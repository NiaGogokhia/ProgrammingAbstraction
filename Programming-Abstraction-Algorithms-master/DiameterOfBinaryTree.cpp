int max(int a, int b){
  return(a>b) ? a:b;
}

int height(Node* root){
  if(root==NULL)return 0;
  return 1+max(height(root->right), height(root->left));
}

int diameter(Node* root){
  if(root==NULL)return 0;
  int lh = height(root->left);
  int rh = height(root->right);
  
  int ld = diameter(root->left);
  int rd = diameter(root->right);
  
  return max(lh+rh+1, max(ld, rd));
}
