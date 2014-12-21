Incompilable branch
===================

This is wht my compiler say:

clang++ -O2 -std=c++11 heaps.cpp  -o heaps.elf                                                 



In file included from heaps.cpp:1:

In file included from ./tests.hpp:9:

In file included from ./heaps.hpp:43:

In file included from ./leftistHeap.hpp:4:

./leftistOrSkewHeap.hpp:45:9: warning: control may reach end of non-void function [-Wreturn-type]

        }

        ^


In file included from heaps.cpp:1:

In file included from ./tests.hpp:9:

In file included from ./heaps.hpp:43:

./leftistHeap.hpp:27:38: error: cannot initialize a parameter of type 'LeftistHeap::Node *' with an lvalue of type 'NMeldableHeaps::LeftistOrSkewHeap::Node *'

                v->rank = 1 + rankOf(v->right);

                                     ^~~~~~~~



./leftistHeap.hpp:18:42: note: passing argument to parameter 'v' here



        size_t rankOf(LeftistHeap::Node *v)



                                         ^



./leftistHeap.hpp:33:38: error: non-const lvalue reference to type 'NMeldableHeaps::LeftistOrSkewHeap::Node *' cannot bind to a value of unrelated type 'LeftistHeap::Node *'

            LeftistOrSkewHeap::meld_(first, second);

                                     ^~~~~

./leftistOrSkewHeap.hpp:28:37: note: passing argument to parameter 'first' here


        virtual Node * meld_(Node *&first, Node *&second)

                                    ^

In file included from heaps.cpp:1:

In file included from ./tests.hpp:9:


In file included from ./heaps.hpp:43:

./leftistHeap.hpp:34:24: error: cannot initialize a parameter of type 'LeftistHeap::Node *' with an lvalue of type 'NMeldableHeaps::LeftistOrSkewHeap::Node *'

            if (rankOf(first->left) < rankOf(first->right))

                       ^~~~~~~~~~~

./leftistHeap.hpp:18:42: note: passing argument to parameter 'v' here


        size_t rankOf(LeftistHeap::Node *v)

                                         ^

./leftistHeap.hpp:34:46: error: cannot initialize a parameter of type 'LeftistHeap::Node *' with an lvalue of type 'NMeldableHeaps::LeftistOrSkewHeap::Node *'

            if (rankOf(first->left) < rankOf(first->right))

                                             ^~~~~~~~~~~~

./leftistHeap.hpp:18:42: note: passing argument to parameter 'v' here


        size_t rankOf(LeftistHeap::Node *v)
                                         ^


In file included from heaps.cpp:1:

./tests.hpp:103:21: warning: enumeration value 'OPERATIONS_NUMBER' not handled in switch [-Wswitch]

            switch (currentQueryType)

                    ^

2 warnings and 4 errors generated.
