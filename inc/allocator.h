/*********************************************************************************************************************
 * @file     allocator.h
 * @brief    Custom Memory Allocator header
 * @version  1.0.0
 * @date     06/02/2022
 *
 */
/******************************************************************************
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/
#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_


#include <limits>
#include "mem.h"


template<typename T>
class object_traits
{
public:

   typedef T type;

   template<typename U>
   struct rebind
   {
      typedef object_traits<U> other;
   };

   // Constructor
   object_traits(void){}

   // Copy Constructor
   template<typename U>
   object_traits(object_traits<U> const& other){}

   // Address of object
   type*       address(type&       obj) const {return &obj;}
   type const* address(type const& obj) const {return &obj;}

   // Construct object
   void construct(type* ptr, type const& ref) const
   {
      // In-place copy construct
      new(ptr) type(ref);
   }

   // Destroy object
   void destroy(type* ptr) const
   {
      // Call destructor
      ptr->~type();
   }
};


#define ALLOCATOR_TRAITS(T)                \
typedef T                 type;            \
typedef type              value_type;      \
typedef value_type*       pointer;         \
typedef value_type const* const_pointer;   \
typedef value_type&       reference;       \
typedef value_type const& const_reference; \
typedef std::size_t       size_type;       \
typedef std::ptrdiff_t    difference_type; \


template <class T>
struct CustomMAllocator
{
  ALLOCATOR_TRAITS(T)

  template<typename U>
  struct rebind
  {
      typedef CustomMAllocator<U> other;
  };
 
  CustomMAllocator () = default;
  template <class U> constexpr CustomMAllocator (const CustomMAllocator <U>&) noexcept {}
 
  [[nodiscard]] T* allocate(std::size_t n) {
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
      throw std::bad_array_new_length();
 
    if ( auto p = static_cast<T*>(Malloc(n*sizeof(T))) ) {
      report(p, n);
      return p;
    }
 
    throw std::bad_alloc();
  }
 
  void deallocate(T* p, std::size_t n) noexcept {
    report(p, n, 0);
    Free(p);
  }
 
private:
  void report(T* p, std::size_t n, bool alloc = true) const {
    std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T)*n
      << " bytes at " << std::hex << std::showbase
      << reinterpret_cast<void*>(p) << std::dec << '\n';
  }
};


#define FORWARD_ALLOCATOR_TRAITS(C)                  \
typedef typename C::value_type      value_type;      \
typedef typename C::pointer         pointer;         \
typedef typename C::const_pointer   const_pointer;   \
typedef typename C::reference       reference;       \
typedef typename C::const_reference const_reference; \
typedef typename C::size_type       size_type;       \
typedef typename C::difference_type difference_type; \

template<typename T,
         typename PolicyT = CustomMAllocator<T>,
         typename TraitsT = object_traits<T> >
class allocator : public PolicyT,
                  public TraitsT
{
public:

    // Template parameters
    typedef PolicyT Policy;
    typedef TraitsT Traits;

    FORWARD_ALLOCATOR_TRAITS(Policy)

    template<typename U>
    struct rebind
    {
       typedef allocator<U,
                         typename Policy::template rebind<U>::other,
                         typename Traits::template rebind<U>::other
                        > other;
    };

    // Constructor
    allocator(void){}

    // Copy Constructor
    template<typename U,
             typename PolicyU,
             typename TraitsU>
    allocator(allocator<U,
                        PolicyU,
                        TraitsU> const& other) :
       Policy(other),
       Traits(other)
    {}
};


// Two allocators are not equal unless a specialization says so
template<typename T, typename PolicyT, typename TraitsT,
         typename U, typename PolicyU, typename TraitsU>
bool operator==(allocator<T, PolicyT, TraitsT> const& left,
                allocator<U, PolicyU, TraitsU> const& right)
{
   return false;
}

// Also implement inequality
template<typename T, typename PolicyT, typename TraitsT,
         typename U, typename PolicyU, typename TraitsU>
bool operator!=(allocator<T, PolicyT, TraitsT> const& left,
                allocator<U, PolicyU, TraitsU> const& right)
{
   return !(left == right);
}

// Comparing an allocator to anything else should not show equality
template<typename T, typename PolicyT, typename TraitsT,
         typename OtherAllocator>
bool operator==(allocator<T, PolicyT, TraitsT> const& left,
                OtherAllocator const& right)
{
   return false;
}

// Also implement inequality
template<typename T, typename PolicyT, typename TraitsT,
         typename OtherAllocator>
bool operator!=(allocator<T, PolicyT, TraitsT> const& left,
                OtherAllocator const& right)
{
  return !(left == right);
}

// Specialize for the heap policy
template<typename T, typename TraitsT,
         typename U, typename TraitsU>
bool operator==(allocator<T, CustomMAllocator<T>, TraitsT> const& left,
                allocator<U, CustomMAllocator<U>, TraitsU> const& right)
{
   return true;
}

// Also implement inequality
template<typename T, typename TraitsT,
         typename U, typename TraitsU>
bool operator!=(allocator<T, CustomMAllocator<T>, TraitsT> const& left,
                allocator<U, CustomMAllocator<U>, TraitsU> const& right)
{
   return !(left == right);
}

#endif  /* allocator.h */

/********************************** End of File ******************************/
