# 快速排序

```C++
inline int partition(vector<int>& nums,int s,int e)
{
    int l=s,r=e;
    
    int cut=nums[s+(e-s>>1)];
    nums[s+(e-s>>1)]=nums[s];
    nums[s]=cut;
   
    while(l<r)
    {
        while(l<r && nums[r]>cut)
            r--;
        nums[l] = nums[r];
        if (l < r)
            l++;
        
        while(l<r && nums[l]<cut)
            l++;
        nums[r] = nums[l];  
        if (l < r)
            r--;  
    }
    nums[l] = cut;
    return l;
}


void qsort(vector<int>& nums,int s,int e)
{
    if(s>=e)
        return;
    
    int mid=partition(nums,s,e);
    qsort(nums,s,mid-1);
    qsort(nums,mid+1,e);
}

vector<int> sortArray(vector<int>& nums) {
    int len = nums.size();
    qsort(nums, 0, len - 1);
    return nums;
}
;
```

# 归并排序

```C
    vector<int> tmp;
    void merge_sort(vector<int>& nums, int l, int r) {
        if (l >= r)
            return;
        int mid = (l + r) >> 1;
        merge_sort(nums, l, mid);
        merge_sort(nums, mid+1, r);

        int i = l, j = mid + 1;
        int cur = l;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                tmp[cur] = nums[i];
                i++;
            } else {
                tmp[cur] = nums[j];
                j++;
            }
            cur++;
        }

        while (i <= mid) {
            tmp[cur++] = nums[i];
            i++;
        }

        while (j <= r) {
            tmp[cur++] = nums[j];
            j++;
        }

        for (int i = l; i <= r; i++)
            nums[i] = tmp[i];
    }

 
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        tmp.assign(len, 0);
        merge_sort(nums, 0, len - 1);
        return nums;
    }
```

# 堆排
```C
    void heap_sort(vector<int>& nums) {
        // build heap
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int index = i + 1;
            while (index != 1) {
                int head = index / 2;
                if (nums[head - 1] < nums[index - 1]) {
                    swap(nums[head-1], nums[index-1]);
                } else {
                    break;
                }
                index = head;
            }
        }

        // 
        int sz = n;
        for (int i = n - 1; i > 0; i--) {
            swap(nums[i], nums[0]);
            sz--;
            int index = 1;
            while ( 2* index <= sz) {
                int lft = 2 * index, rft = 2 * index + 1;
                if (rft > sz) {
                    if (nums[lft-1] > nums[index -1]) {
                        swap(nums[lft-1], nums[index - 1]);
                    }
                    break;
                }

                if (nums[lft-1] > nums[rft - 1]) {
                    if (nums[lft-1] > nums[index -1]) {
                        swap(nums[lft-1], nums[index - 1]);
                        index = lft;
                    } else
                        break;
                } else {
                    if (nums[rft-1] > nums[index -1]) {
                        swap(nums[rft-1], nums[index - 1]);
                        index = rft;
                    } else
                        break;
                }
            }
        }
    }

 
    vector<int> sortArray(vector<int>& nums) {
        heap_sort(nums);
        return nums;
    }

```