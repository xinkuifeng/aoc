# Reflect

The tree structure fits perfectly to this problem:

```cpp
struct TreeNode {
    int val;
    vector<TreeNode *> children;
};
```

Use this data structure to emulate the file system. Compute the size of the tree node
(either file or diretory) recursively. Do level-order-traversal to print the tree
structure and output the sizes of directories.

