#include <iostream>
#include <utility> // std::pair
#include <algorithm> // std::max
#include <stack>

using namespace std;

// MAX 정의
#define MAX(a,b)    ((a>b) ? (a):(b))

// 올려주신 수도코드를 기반으로 코드를 짰습니다.

// 고쳐야할거
// 1. checkBalance tuple 쓰지 않기 + 그래서 std::tie도 고쳐야함.
// pair로 고치면 되나 .
// 2. using namespace 쓰면 안될 수도 있음.

typedef int element;

typedef struct _TREENODE_{
    element key;
    struct _TREENODE_* left;
    struct _TREENODE_* right;
    int height;
    int size;
    int bf;
}TREENODE;

bool insertAVL(TREENODE** root, element newKey);
bool deleteAVL(TREENODE** root, element deleteKey);

TREENODE* rotateLL(TREENODE* parent);
TREENODE* rotateLR(TREENODE* parent);
TREENODE* rotateRR(TREENODE* parent);
TREENODE* rotateRL(TREENODE* parent);

bool insertBST(TREENODE** root, element newKey);
TREENODE* deleteBST(TREENODE** root, element deleteKey);

TREENODE* getNodeBST();
TREENODE* getNodeAVL();

void inorderTraverse(TREENODE* root);
void clearTree(TREENODE* node);

tuple<string, TREENODE*, TREENODE*> checkBalance(TREENODE* root, int newKey);
// void rotateTree(TREENODE** root, string rotateType, TREENODE* p, TREENODE* q);

int height(TREENODE* p);

int height(TREENODE* p){
    int h = 0; // height 구하기
    if(p != NULL){
        h = max(height(p->left),height(p->right))+1;
    }
    return h;
}

// rotate 한다음에 height 재조정 해줘야함 ..
TREENODE* rotateLL(TREENODE* parent){
    TREENODE* a = parent;
    TREENODE* b = parent->left;
    a->left = b->right;
    b->right = a;

    a->bf = 0;
    b->bf = 0;
    b->height = height(b);
    return b; // 루트 노드를 반환해서 이어줌 .
}

TREENODE* rotateRR(TREENODE* p){
    TREENODE* a = p;
    TREENODE* b = p->right;
    a->right = b->left;
    b->left = a;

    a->bf=0;
    b->bf=0;
    b->height = height(b);
    return b;
}

TREENODE* rotateLR(TREENODE* p){
    TREENODE* a = p;
    TREENODE* b = p->left;
    TREENODE* c = b->right;

    b->right = c->left;
    a->left = c->right;
    c->left = b;
    c->right = a;
    switch(c->bf){
        case 0 : b->bf = 0; a->bf = 0; break;
        case 1 : a->bf = -1; b->bf = 0; break;
        case -1 : b->bf = 1; a->bf = 0; break;
    }
    c->bf = 0;
    b = c; // 나는 이거 안해줘도됨. 

    b->height = height(b);
    return b;
}

TREENODE* rotateRL(TREENODE* p){
    TREENODE* a = p;
    TREENODE* b = p->right;
    TREENODE* c = b->left;

    b->left = c->right;
    a->right = c->left;
    c->left = a;
    c->right = b;
    switch(c->bf){
        case 0 : b->bf = 0; a->bf = 0; break; // c의 bf가 0 이면 .. 0 0 0
        case -1 : a->bf = 1; b->bf = 0; break; // c의 bf가 -1이면 .. a가 1.. b는 0
        case 1 : b->bf = -1; a->bf = 0; break; // c의 bf가 1이면 .. b가 -1 .. a는 0
    }
    c->bf = 0; // c의 bf는 0 .. 
    b = c;

    b->height = height(b);
    return b;
}

TREENODE* getNodeBST(){
    TREENODE* newNode = (TREENODE*)calloc(1,sizeof(TREENODE));

    return newNode;
}

bool insertBST(TREENODE** root, element newKey){
    TREENODE* p = *root; // cur
    TREENODE* q = NULL;
    TREENODE* newNode = NULL;

    stack<TREENODE*> stack;

    while(p != NULL){
        if(newKey == p->key){
            // 이미 있는 경우 .
            return true; // 이미 키가 있으면 true를 반환함.
        }

        q = p; // 부모노드 표시해주고
        stack.push(q); // 스택에 넣어줌.

        if(newKey < p->key){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }
    // create new node (삽입할 위치를 찾은 경우)
    // getNodeBST() 함수를 따로 만들지 않고 바로 구현하였습니다.
    newNode = getNodeBST();
    newNode->key = newKey;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    newNode->size = 1;

    if(q == NULL){
        *root = newNode;
    }
    else{
        if(newKey < q->key){
            q->left = newNode;
        }else{
            q->right = newNode;
        }
    }

    while(!stack.empty()){
        q = stack.top(); stack.pop();
        q->height = 1 + max(q->left ? q->left->height : 0, q->right ? q->right->height : 0);
        q->size += 1;
        // size 함수를 따로 만들지 않고 스택에 넣어두었던 조상 노드들을 pop할때 size -= 1을 해주었습니다.
    }

    return false; // 같은 키를 찾지 못했으면 false를 반환함.
}

// 삭제한 노드의 부모 노드를 반환해야함 .
// 부모노드 어떻게 반환하노
TREENODE* deleteBST(TREENODE** root, element deleteKey){
    TREENODE* p = *root;
    TREENODE* q = NULL; // parent

    stack<TREENODE*> stack;
    // find position of deleteKey while storing parent node on stack
    // 삭제할 노드의 위치를 탐색함 .
    while(p != NULL && deleteKey != p->key){
        q = p;
        stack.push(q);
        if(deleteKey < p->key){
            p = p->left;
        }
        else if(deleteKey > p->key){
            p = p->right;
        }
    }

    // 삭제할 노드가 없는 경우 ..
    if(p == NULL){
        return NULL;
    }

    // 차수가 0이면 .
    if((p->left == NULL) && (p->right == NULL)){
        if(q == NULL){
            *root = NULL; // 부모가 없으면 루트노드 삭제
        }else{
            if(q->left == p){
                q->left = NULL; // 차수 0이니까 그냥 삭제해주면 됨.
            }
            else{
                q->right = NULL;
            }
        }
    }else if(p->left == NULL || p->right == NULL){
        // 차수가 1인경우
        
        TREENODE* child = NULL;
        // child가 p의 왼쪽에 있는지 오른쪽에 있는지 정함.
        if(p->left != NULL){
            child = p->left;
        }else{
            child = p->right;
        }
        
        if(q != NULL){
            if(q->left == p){
                q->left = child;
            }else{
                q->right = child;
            }
        }else{
            // p의 부모가 없는 경우 .. 노드가 두개만 존재할떄
            *root = child; // 그냥 루트를 child로 만들어 주면 됨 .
        }
    }else{
        // 차수가 2인 경우 ..
        TREENODE* temp = p; // 삭제될 노드를 temp에 저장해둠 ..

        stack.push(p);
        // 오른쪽 트리에서 가장 작은 노드를 후계자로 선택하는 경우
        // 높이가 오른쪽이 높거나, 높이는 같은데 사이즈가 오른쪽이 큰경우
        // (p의 차수가 2인 경우니까 p->left, p->right가 NULL일 경우는 없음)
        if((p->left->height < p->right->height) || ((p->left->height == p->right->height) && p->left->size < p->right->size)){
            p = p->right;
            // 오른쪽에서 가장 작은 노드 찾기
            // minNode();
            while(p->left != NULL){
                stack.push(p);
                p = p->left;
            }

            q = stack.top(); // q는 후계자의 부모노드를 가리킴

            if(q->right == p){
                // 오른쪽 트리의 처음 노드가 왼쪽 자식이 없는 경우 ..(특수한 경우)
                q->right = p->right;
            }
            else{
                q->left = p->right;
            }

            temp->key = p->key;
            temp = p; // 후계자를 temp에 넣고 삭제
        }else{
            // 왼쪽 트리에서 가장 큰 노드를 후계자로 선택하는 경우
            // 높이가 왼쪽이 높거나, 높이는 같은데 사이즈가 왼쪽이 큰 경우
            p = p->left;
            // 왼쪽에서 가장 큰 노드 찾기
            while(p->right != NULL){
                stack.push(p);
                p = p->right;
            }

            q = stack.top(); // q는 후계자의 부모노드를 가리킴

            if(q->left == p){
                q->left = p->left;
            }
            else{
                q->right = p->left;
            }

            temp->key = p->key;
            temp = p;
        }
    }

    delete p;

    TREENODE* parentNode = NULL;
    // update height while popping parent node from stack
    // stack에 쌓아뒀던 노드들의 사이즈를 하나씩 줄여줌.

    bool flag = false; // flag를 이용해서 가장 첫번째 조상노드, 즉 삭제된 노드의 부모를 저장함.
    while(!stack.empty()){
        q = stack.top(); stack.pop();
        if(!flag){
            parentNode = q;
            flag = true;
        }
        // q->left, q->right가 NULL인 경우 예외처리
        q->height = 1 + max(q->left ? q->left->height : 0, q->right ? q->right->height : 0); 
        q->size -= 1;
        // size 함수를 따로 만들지 않고 스택에 넣어두었던 조상 노드들을 pop할때 size -= 1을 해주었습니다.
    }
    
    return parentNode;
}

tuple<string, TREENODE*, TREENODE*> checkBalance(TREENODE* root, int newKey){
    string rotateType;

    TREENODE* f = NULL; // 반환할 불균형 노드의 부모를 저장할 포인터.
    TREENODE* a = root;
    TREENODE* b = NULL;

    TREENODE* p = root;
    TREENODE* q = NULL;

    // step 1: 새로 삽입된 newKey의 위치 q를 찾음
    while(p != NULL){
        if(p->bf != 0){
            // 불균형이 탐지된 가장 가까운 조상 노드를 찾음.
            // 찾아 들어가면서 균형인수가 0이 아닌 노드가 불균형이 탐지된 가장 가까운 조상 노드임 .
            // a는 불균형 노드일 수도 있고, 아닐 수도 있음. 밑에서 판단을 해줘야한다.
            a = p;
            f = q;
        }

        if(newKey < p->key){
            q = p;
            p = p->left;
        }
        else if(newKey > p->key){
            q = p;
            p = p->right;
        }
        else{
            // newKey를 찾은 경우.
            q = p;
            p = NULL;
            break;
        }
    }

    // step 2: bf계산
    // 새로 삽입된 newKey의 위치 q를 찾음 .

    int d=0; // d는 그냥 삽입 노드가 불균형 노드의 왼쪽 서브트리에 있는지, 오른쪽 서브 트리에 있는지 나타냄.
    // d = 1이면 왼쪽 서브트리 .., d = -1이면 오른쪽 서브트리 라는 뜻이다.

    // a -> 불균형 노드 ..
    if(newKey < a->key){
        // newKey가 불균형 노드의 왼쪽에 있는 경우
        p = a->left;
        b = p; // b는 a의 자식
        d = 1; // 불균형 노드의 왼쪽에 삽입 됐으면, 균형인수는 1
    }
    else{
        p = a->right;
        b = p;
        d = -1; // 불균형 노드의 오른쪽에 삽입 됐으면, 균형인수는 -1
    }

    // 여기서의 반복은 bf가 다 0인 경우 밖에 없음
    // a가 bf != 0인 가장 가까운 조상 노드 였기 때문에 ..
    while(p != q){
        if(newKey < p->key){
            p->bf = 1; // p를 q로 이동시키면서 
            p = p->left;
        }
        else{
            p->bf = -1;
            p = p->right;
        }
    }

    // step3: 트리의 균형 여부 검사 및 회전 유형 결정
    bool unbalanced = true;

    // a는 일단 균형인수가 0이 아닌 가장 가까운 노드를 찾은것임.
    // 이 노드가 불균형 노드일 수도 있고, 아닐 수도 있다.
    // d는 .. a의 자식의 균형 인수이다.

    // 트리가 아직 균형인 경우 ..
    if(a->bf + d != -2 || a->bf + d != 2){
        a->bf += d; // 이 값은 항상 0이다. 1-1 or -1+1
        unbalanced = false;
    }
    rotateType = "NO";

    if(unbalanced == true){
        // d는 1인 경우
        if(d == 1){ // 왼쪽 불균형인 경우 . 
            if(b->bf == 1){ // a의 자식이 1인 경우
                rotateType = "LL";
            }
            else{ // a의 자식이 -1 인경우 ..
                rotateType = "LR";
            }
        }
        else{ // d는 -1 인경우 -> 오른쪽 불균형인 경우 .
            if(b->bf == 1){ // b의 자식이 1인 경우
                rotateType = "RL";
            }
            else{
                rotateType = "RR";
            }
        }
    }

    return {rotateType,a,f};
}

TREENODE* getNodeAVL(){
    TREENODE* newNode = (TREENODE*)calloc(1,sizeof(TREENODE));

    return newNode;
}

void rotateTree(TREENODE** root, string rotateType, TREENODE* p, TREENODE* q){
    TREENODE* a = NULL; // 반환할 불균형 노드 저장할 포인터
    TREENODE* b = NULL; // newKey가 삽입된, 불균형 노드 a의 자식을 저장할 포인터 ..
    TREENODE* c = NULL; 

    if(rotateType == "LL"){
        // p -> 불균형이 탐지된 가장 가까운 노드 ..
        a = p;
        b = p->left;
        a->left = b->right;
        b->right = a;

        a->bf = 0;
        b->bf = 0;
    }else if(rotateType == "LR"){
        a = p;
        b = p->left;
        c = b->right;

        b->right = c->left;
        a->left = c->right;
        c->left = b;
        c->right = a;
        switch(c->bf){
            case 0: b->bf = 0; a->bf = 0; break; // c의 bf가 0인 경우
            case 1: a->bf = -1; b->bf = 0; break; // c의 bf가 1인 경우, c의 자식중 높이가 큰 자식이 b에 붙음
            case -1: b->bf = 1; a->bf = 0; break; // c의 bf가 -1인 경우, c의 자식중 높이가 큰 자식이 a에 붙음.
        }
        c->bf = 0; b = c; // b가 루트노드가 된다.
    }else{
        if(rotateType == "RR"){
            a = p;
            b = p->right;
            a->right = b->left;
            b->left = a;

            a->bf = 0;
            b->bf = 0;
        }else if(rotateType == "RL"){
            a = p;
            b = p->right;
            c = b->left;

            b->left = c->right; // b의 자식 정해주고
            a->right = c->left; // a의 자식을 정해줌 . c는 루트니까.
            c->right = b;
            c->left = a;
        }
    }

    if(q == NULL){
        *root = b;
    }
    else if(a == q->left){
        q->left = b; // 원래 트리랑 이어줘야함.
    }
    else if(a == q->right){
        q->right = b;
    }
}

bool insertAVL(TREENODE** root, element newKey){
    TREENODE* p = *root;
    TREENODE* q = NULL;
    TREENODE* x = NULL; // y의 삭제로 인하여 불균형으로 판명된 최초 노드 ..
    TREENODE* f = NULL;

    TREENODE* newNode = NULL;

    stack<TREENODE*> stack;

    // find position to insert newKey while storing parent node on stack
    while(p != NULL){
        if(newKey == p->key){
            return false; // 이미 키가 있으면 false를 반환함.
        }
        q = p;
        stack.push(q);
        
        if(newKey < p->key){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }
    // p == NULL이 되고 q는 삽입한 노드의 position..

    // create new node
    newNode = getNodeAVL();
    newNode->key = newKey;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    newNode->size = 1;
    newNode->bf = 0;

    if(*root == NULL){
        *root = newNode; // T <- y
    }
    else{
        if(newKey < q->key){
            q->left = newNode;
        }
        else{
            q->right = newNode;
        }
    }

    // update height and balancing factor while popping parent node from stack
    while(!stack.empty()){
        q = stack.top(); stack.pop();
        q->size += 1;

        // 1. height함수를 이용해서 q->left와 q->right의 높이를 구한다.
        // q->left와 q->right의 높이를 이용해서 q->bf를 구한다.
        q->bf = (q->left ? height(q->left): 0) - (q->right ? height(q->right) : 0);
        // 큐에서 빼면서 .. 균형인수 초기화해줌.
        if(1 < q->bf || q->bf < -1){
            if(x == NULL){
                x = q; // x -> 불균형으로 판명된 최초의 노드 ..

                if(!stack.empty()){
                    f = stack.top();
                }
            }
        }
    }

    // Step2 : 군형 검사

    // 밸런스를 맞추지 않아도 되는 경우 그냥 끝냄 ..
    if(x == NULL) return true;
    // 불균형 발생한 트리를 rebalacing 하고 부모노드와 이어주는 방식으로 구현하겠습니다.
    
    // f -> 불균형 노드의 부모 !.
    // f가 NULL 인 경우와 f가 있는 경우로 나누어야함.
    if(1 < x->bf){
        if(0 < x->left->bf){
            if(f == NULL){
                // f가 NULL인 경우 .. 균형을 맞추고 반환되는 노드가 루트노드임
                *root = rotateLL(x);

                // 밸런스를 맞추고 height랑 bf를 다시 다 계산해줘야함.
            }
            else{
                // f가 NULL이 아니면 .. 균형을 맞추고 반환되는 노드를 부모노드랑 이어주면 된다.
                if(f->left == x){
                    f->left = rotateLL(x);
                }
                else{
                    f->right = rotateLL(x);
                }
            }
        }
        else{
            if(f == NULL){
                // f가 NULL인 경우 .. 균형을 맞추고 반환되는 노드가 루트노드임
                *root = rotateLR(x);
            }
            else{
                // f가 NULL이 아니면 .. 균형을 맞추고 반환되는 노드를 부모노드랑 이어주면 된다.
                if(f->left == x){
                    f->left = rotateLR(x);
                }
                else{
                    f->right = rotateLR(x);
                }
            }
        }
    }
    else if(x->bf < -1){
        if(x->right->bf < 0){
            if(f == NULL){
                // f가 NULL인 경우 .. 균형을 맞추고 반환되는 노드가 루트노드임
                *root = rotateRR(x);
            }
            else{
                // f가 NULL이 아니면 .. 균형을 맞추고 반환되는 노드를 부모노드랑 이어주면 된다.
                if(f->left == x){
                    f->left = rotateRR(x);
                }
                else{
                    f->right = rotateRR(x); 
                }
            }
        }
        else{
            if(f == NULL){
                // f가 NULL인 경우 .. 균형을 맞추고 반환되는 노드가 루트노드임
                *root = rotateRL(x);
            }
            else{
                // f가 NULL이 아니면 .. 균형을 맞추고 반환되는 노드를 부모노드랑 이어주면 된다.
                if(f->left == x){
                    f->left = rotateRL(x);
                }
                else{
                    f->right = rotateRL(x);
                }
            }
        }
    }
    // p-> 불균형 위치, q -> p의 부모

    return true;
}

bool deleteAVL(TREENODE** root, int deleteKey){
    TREENODE* p = *root;
    TREENODE* q = NULL;
    TREENODE* x = NULL;
    TREENODE* f = NULL;

    stack<TREENODE*> stack;
    // 삭제할 키의 위치를 찾는다. p -> 삭제할 키의 위치.
    while(p != NULL && deleteKey != p->key){
        q = p;
        stack.push(q);

        if(deleteKey < p->key){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }

    // 삭제할 키가 트리에 없으면 return
    if(p == NULL){
        return false;
    }

    // 차수가 0인 경우
    if(p->left == NULL && p->right == NULL){
        if(q == NULL){
            *root = NULL; // 부모가 없으면 루트노드 삭제
        }
        else{
            if(q->left == p){
                q->left = NULL;
            }
            else{
                q->right = NULL;
            }
        }
    }
    else if(p->left == NULL || p->right == NULL){
        TREENODE* child = NULL;
        
        if(p->left != NULL){
            child = p->left;
        }
        else{
            child = p->right;
        }
        if(q != NULL){
            if(q->left == p){
                q->left = child;
            }
            else{
                q->right = child;
            }
        }
        else{
            // 부모가 없는 경우 p의 자식인 child가 루트노드가 된다.
            *root = child;
        }
    }
    else{
        // 차수가 2인 경우..
        TREENODE* temp = p; 
        // p를 temp에 저장해둠 ..
        stack.push(p);

        if((p->left->height < p->right->height) || ((p->left->height == p->right->height) && (p->left->size < p->right->size))){
            p = p->right; // p의 오른쪽에서 가장 작은 노드를 찾음.

            // minNode();
            while(p->left != NULL){
                stack.push(p);
                p = p->left;
            }

            q = stack.top(); // q는 후계자 노드의 부모

            // 후계자의 부모와 후계자의 자식을 이어준다.
            if(q->right == p){
                // 오른쪽 트리의 루트노드가 키가 가장 작은 노드인 경우
                q->right = p->right;
            }
            else{
                q->left = p->right;
            }

            temp->key = p->key;
            temp = p; // 메모리 해제를 위해 temp가 후계자 노드를 가리키게함.
        }
        else{
            // 높이가 왼쪽이 높거나, 높이는 같은데 사이즈가 왼쪽이 커서 삭제하는 경우
            p = p->left;
            // p의 왼쪽 트리에서 키값이 가장 큰 노드를 찾는다.
            // maxNode();
            while(p->right != NULL){
                stack.push(p);
                p = p->right;
            }

            q = stack.top(); // q는 후계자의 부모 노드를 가리킴.

            // 삭제할 노드의 부모와 삭제할 노드의 자식을 이어준다.
            if(q->left == p){
                q->left = p->left;
            }
            else{
                q->right = p->left;
            }

            // 노드 삭제.
            temp->key = p->key;
            temp = p;
        }

        // temp에 저장해뒀던 삭제할 노드를 delete함.
        delete temp;
    }

    while(!stack.empty()){
        q = stack.top(); stack.pop();
        // q->left, q->right가 NULL인 경우 예외처리
        q->height = 1 + max(q->left ? q->left->height : 0, q->right ? q->right->height : 0); 
        q->size -= 1;
        // size 함수를 따로 만들지 않고 스택에 넣어두었던 조상 노드들을 pop할때 size -= 1을 해주었습니다.
        
        q->bf = (q->left ? height(q->left): 0) - (q->right ? height(q->right) : 0);

        if(q->bf < -1 || 1 < q->bf){
            x = q;
            f = NULL;

            if(!stack.empty()){
                f = stack.top(); 
            }
            
            // f가 NULL인 경우가 있을 수 있음. (삭제되는 노드가 부모가 없는 경우)
            if(1 < x->bf){
                if(0 < x->left->bf){
                    if(f == NULL){
                        *root = rotateLL(x);
                    }
                    else{
                        if(f->left == x){
                            f->left = rotateLL(x);
                        }
                        else{
                            f->right = rotateLL(x);
                        }
                    }
                }
                else{
                    if(f == NULL){
                        *root = rotateLR(x);
                    }
                    else{
                        if(f->left == x){
                            f->left = rotateLR(x);
                        }
                        else{
                            f->right = rotateLR(x);
                        }
                    }
                }
            }
            else if(x->bf < -1){
                if(x->right->bf < 0){
                    if(f == NULL){
                        *root = rotateRR(x);
                    }
                    else{
                        if(f->left == x){
                            f->left = rotateRR(x);
                        }
                        else{
                            f->right = rotateRR(x);
                        }
                    }
                }
                else{
                    if(f == NULL){
                        *root = rotateRL(x);
                    }
                    else{
                        if(f->left == x){
                            f->left = rotateRL(x);
                        }
                        else{
                            f->right = rotateRL(x);
                        }
                    }
                }
            }
        }
    }

    return true;
}

// 후위순회로 clear
void clear(TREENODE* node){
    if(node == nullptr) return;

    clear(node->left);
    clear(node->right);

    delete node;
    node = nullptr;
}

void inorder(TREENODE* node){
    if(node == NULL){
        return;
    }
    cout << "<";
    inorder(node->left);
    cout << " " << node->key << " ";
    inorder(node->right);
    cout << ">";
}

int main(){
    char command;
    int key;

    TREENODE* root = NULL;

    while(cin >> command >> key){
        if(command == 'i'){
            if(insertAVL(&root,int(key)) == false){
                printf("i %d: The key already exists\n", key);
                continue;
            }
        }
        else if(command == 'd'){
            if(deleteAVL(&root, int(key)) == false){
                printf("d %d: The key does not exist\n", key);
                continue;
            }
        }
        else{
            cout << "Invalid command: " << command << "\n";
            return (1);
        }

        inorder(root);
        cout << "\n";
    }

    // 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
    clear(root);

    return (0);
}