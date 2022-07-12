//Binary Search (while)
bool binarySearch(arr, int low, int up, int x){
  while(low <= up){
    int mid = low+(up-low)/2;
    if(mid==x)return true;
    if(arr[mid]<x)low=mid+1;
    else up = mid-1;
  }
  return false;
}
