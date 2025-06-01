#4023613060 محمد کریمی
#4023613068 امیررضا محمدی یگانه
#Partition of a set into K subsets with equal sum

def can_partition_branch_bound(nums , k):
    tot_sum = sum(nums)
    if tot_sum % k != 0 or len(nums) < k:
        return False
    
    target = tot_sum // k
    nums.sort(reverse=True)
    
    if nums[0] > target:
        return False
    
    def calculate_bound(index, buckets):
        remaining_sum = sum(nums[index:])
        remaining_capacity = sum(target - bucket for bucket in buckets)
        return remaining_sum <= remaining_capacity
    
    def branch_bound(index, buckets):
        if not calculate_bound(index, buckets):
            return False
        
        if index == len(nums):
            return True
        
        for i in range(k):
            if buckets[i] + nums[index] <= target:
                buckets[i] += nums[index]
                
                if branch_bound(index+1, buckets):
                    return True

                buckets[i] -= nums[index]
                if buckets[i] == 0:
                    break
                
        
        return False
    
    return branch_bound(0, [0] * k)
                
                



nums = list(map(int, input().strip().split(',')))
k = int(input())

print(can_partition_branch_bound(nums, k))