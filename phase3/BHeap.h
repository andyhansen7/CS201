
class HeapNode
{
    public:
        KEYTYPE key = 0;

        HeapNode* parent = NULL;
        HeapNode* rightSibling = NULL;
        HeapNode* leftSibling = NULL;
        HeapNode* child = NULL;
}