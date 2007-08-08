/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

#include <boost/intrusive/linking_policy.hpp>

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type and
//!node_traits::node should be equal
template<class NodeTraits, linking_policy LinkingPolicy = safe_link>
struct trivial_value_traits
{
   typedef NodeTraits                                          node_traits;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef typename node_traits::const_node_ptr                const_node_ptr;
   typedef typename node_traits::node                          value_type;
   typedef node_ptr                                            pointer;
   typedef const_node_ptr                                      const_pointer;
   enum {   linking_policy =  LinkingPolicy  };
   static node_ptr to_node_ptr (value_type &value)             {  return node_ptr(&value); }
   static const_node_ptr to_node_ptr (const value_type &value) {  return const_node_ptr(&value); }
   static pointer to_value_ptr(node_ptr n)                     {  return pointer(n); }
   static const_pointer to_value_ptr(const_node_ptr n)         {  return const_pointer(n); }
};

} //namespace intrusive 
} //namespace boost 

#endif //BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP