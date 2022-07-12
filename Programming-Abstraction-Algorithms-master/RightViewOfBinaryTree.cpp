void recursion(TreeNode* root, int lvl, vector<int>&res){
  if(root==NULL)return;
  if(res.size()==lvl)res.push_back(root->val);
  recursion(root->right, lvl+1, res);
  recursion(root->left, lvl+1, res);
}

vector<int> rightSideView(TreeNode* root){
  vector<int> res;
  recursion(root, 0, res);
  return res;
}
