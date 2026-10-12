#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <sstream>

// Structure to represent a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to build a binary tree from preorder traversal with -1 as null
TreeNode* buildTree(std::vector<int>& preorder, int& index) {
    if (index >= preorder.size() || preorder[index] == -1) {
        index++;
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(preorder[index++]);
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);
    
    return root;
}

// Function to find depth and parent of each node
void findDepthAndParent(TreeNode* root, int depth, int parent, 
                       std::unordered_map<int, int>& nodeDepth, 
                       std::unordered_map<int, int>& nodeParent) {
    if (!root) return;
    
    // Store depth and parent of current node
    nodeDepth[root->val] = depth;
    nodeParent[root->val] = parent;
    
    // Recursively process left and right subtrees
    findDepthAndParent(root->left, depth + 1, root->val, nodeDepth, nodeParent);
    findDepthAndParent(root->right, depth + 1, root->val, nodeDepth, nodeParent);
}

// Function to delete the tree to prevent memory leaks
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int q;
    std::cin >> q;
    
    // Read the query pairs
    std::vector<std::pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        std::cin >> queries[i].first >> queries[i].second;
    }
    
    // Read the preorder traversal
    std::string line;
    std::getline(std::cin, line); // consume the newline after the last query
    std::getline(std::cin, line);
    
    std::vector<int> preorder;
    std::stringstream ss(line);
    int val;
    while (ss >> val) {
        preorder.push_back(val);
    }
    
    // Build the tree from preorder traversal
    int index = 0;
    TreeNode* root = buildTree(preorder, index);
    
    // Find depth and parent of each node
    std::unordered_map<int, int> nodeDepth;
    std::unordered_map<int, int> nodeParent;
    findDepthAndParent(root, 0, -1, nodeDepth, nodeParent);
    
    // Process each query
    for (int i = 0; i < q; i++) {
        int x = queries[i].first;
        int y = queries[i].second;
        
        // Check if nodes exist and are cousins
        if (nodeDepth.find(x) != nodeDepth.end() && 
            nodeDepth.find(y) != nodeDepth.end() &&
            nodeDepth[x] == nodeDepth[y] && 
            nodeParent[x] != nodeParent[y]) {
            std::cout << 1 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    
    // Clean up memory
    deleteTree(root);
    
    return 0;
}