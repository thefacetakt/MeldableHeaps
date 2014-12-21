Yet Another Experimenal branch, which I can't compile
=====================================================



In file included from heaps.cpp:1:

In file included from ./tests.hpp:9:

In file included from ./heaps.hpp:50:

./leftistHeap.hpp:105:12: error: no member named 'insert' in 'NMeldableHeaps::LeftistOrSkewHeap<EM_LEFTIST>'

        x->insert(5);
        
        ~  ^
        
./leftistHeap.hpp:106:19: error: no member named 'getMinimalElement' in 'NMeldableHeaps::LeftistOrSkewHeap<EM_LEFTIST>'

        return x->getMinimalElement();
        
               ~  ^
               
In file included from heaps.cpp:1:

In file included from ./tests.hpp:9:

./heaps.hpp:64:24: error: cannot initialize return object of type 'NMeldableHeaps::IHeap *' with an rvalue of type 'LeftistHeap *' (aka 'LeftistOrSkewHeap<EM_LEFTIST> *')

                return new LeftistHeap();
                
                       ^~~~~~~~~~~~~~~~~
                       
In file included from heaps.cpp:1:

./tests.hpp:103:21: warning: enumeration value 'OPERATIONS_NUMBER' not handled in switch [-Wswitch]

            switch (currentQueryType)
            
                    ^
                    
1 warning and 3 errors generated.