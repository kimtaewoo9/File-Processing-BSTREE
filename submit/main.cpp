#include <iostream>
#include <stack>

using namespace std;

// 메모리 누수x -> 후위 순회로 메모리 해제해야함.
//

typedef int element;

typedef struct _TREENODE_{
    element key;
    struct _TREENODE_* left;
    struct _TREENODE_* right;
    int height;
    int size;

}TREENODE;

bool insertBST(TREENODE** root, element newKey);
bool deleteBST(TREENODE** root, element deleteKey);
TREENODE* getNodeBST();
int getMax(int a,int b);
TREENODE* getMaxNode(TREENODE* root);
TREENODE* getMinNode(TREENODE* root);
void inorderTraverse(TREENODE* node);

bool insertBST(TREENODE** root, element newKey){
    TREENODE* p = *root; // cur
    TREENODE* q = NULL;
    TREENODE* newNode = NULL;

    stack<TREENODE*> stack;

    while(p != NULL){
        if(newKey == p->key){
            // 이미 있는 경우 .
            return false;
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
    newNode = (TREENODE*)calloc(1,sizeof(TREENODE));
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
        q->height = 1 + getMax(q->left ? q->left->height : 0, q->right ? q->right->height : 0);
        q->size += 1;
        // size 함수를 따로 만들지 않고 스택에 넣어두었던 조상 노드들을 pop할때 size -= 1을 해주었습니다.
    }

    return true;
}

int getMax(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

bool deleteBST(TREENODE** root, element deleteKey){
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
        return false;
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

    // update height while popping parent node from stack
    // stack에 쌓아뒀던 노드들의 사이즈를 하나씩 줄여줌.
    while(!stack.empty()){
        q = stack.top(); stack.pop();
        // q->left, q->right가 NULL인 경우 예외처리
        q->height = 1 + getMax(q->left ? q->left->height : 0, q->right ? q->right->height : 0); 
        q->size -= 1;
        // size 함수를 따로 만들지 않고 스택에 넣어두었던 조상 노드들을 pop할때 size -= 1을 해주었습니다.
    }
    
    return true;
}

TREENODE* getMaxNode(TREENODE* root){
    TREENODE* cur = root;
    while(root->right != NULL){
        cur = cur->right;
    }
    return cur;
}

TREENODE* getMinNode(TREENODE* root){
    TREENODE* cur = root;
    while(root->left != NULL){
        cur = cur->left;
    }
    return cur;
}

void inorderTraverse(TREENODE* node){
    if(node == NULL){
        return;
    }
    cout << "< ";
    inorderTraverse(node->left);
    printf("%d", node->key);
    inorderTraverse(node->right);
    cout << " >";
}

// clear 는 .. 후위순회로 클리어 해야함
// 자식 노드부터 삭제해야하기 때문에
void clearTree(TREENODE* node){
    if(node == NULL) return;

    clearTree(node->left);
    clearTree(node->right);

    delete(node);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    char command;
    int key;

    TREENODE* root = NULL;

    while(cin >> command >> key){
        if(command == 'i'){
            if(insertBST(&root,int(key)) == false){
                printf("i %d:The key already exists\n", key);
                continue;
            }
        }
        else if(command == 'd'){
            if(deleteBST(&root, int(key)) == false){
                printf("d %d:The key does not exist\n", key);
                continue;
            }
        }
        else{
            cout << "Invalid command: " << command << "\n";
            return (1);
        }

        inorderTraverse(root);
        cout << "\n";
    }

    // 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
    clearTree(root);

    return (0);
}