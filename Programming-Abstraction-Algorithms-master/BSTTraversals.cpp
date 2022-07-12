
void inorder(Node* root){
  inorder(root->left);
  cout << root->val << endl;
  inorder(root->right);
}

void preorder(Node* root){
  cout << root->val << endl;
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node* root){
  postorder(root->left);
  postorder(root->right);
  cout << root->val << endl;
}
