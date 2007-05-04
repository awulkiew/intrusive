/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//[doc_clone_from
#include <boost/intrusive/list.hpp>
#include <iostream>
#include <vector>

//A class that can be inserted in an intrusive list
class my_class 
   :  public boost::intrusive::list_base_hook<>
{
   public:
   friend bool operator==(const my_class &a, const my_class &b)
   {  return a.int_ == b.int_;   }

   int int_;

   //...
};

//Definition of the intrusive list
typedef boost::intrusive::list< my_class::value_traits<my_class> > my_class_list;

//Cloner object function
class new_cloner
{
   public:
   my_class *operator()(const my_class &clone_this)
   {  return new my_class(clone_this);  }
};

//The destroyer object function
class delete_destroyer
{
   public:
   void operator()(my_class *delete_this)
   {  delete delete_this;  }
};

int main()
{
   const int MaxElem = 100;
   std::vector<my_class> nodes(MaxElem);

   //Fill all the nodes and insert them in the list
   my_class_list list;

   for(int i = 0; i < MaxElem; ++i){
      nodes[i].int_ = i;
   }
   list.insert(list.end(), nodes.begin(), nodes.end());

   //Now clone "list" using "new" and "delete" object functions
   my_class_list cloned_list;
   cloned_list.clone_from(list, new_cloner(), delete_destroyer());

   //Test that both are equal
   if(cloned_list != list){
      std::cout << "Both lists are different" << std::endl;
   }
   else{
      std::cout << "Both lists are equal" << std::endl;
   }

   //Don't forget to free the memory from the second list
   cloned_list.clear_and_destroy(delete_destroyer());
   return 0;
}
//]
