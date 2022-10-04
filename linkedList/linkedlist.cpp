struct node {
    int value;
    struct node* next;
};
typedef struct node node_t;


int main() {
    node_t n1, n2, n3;
    node_t *head;

    n1.value = 45;
    n2.value = 22;
    n3.value = 1;

    head = &n3;
    n3.next = &n2;
    n2.next = &n1;
    return 0;
}
