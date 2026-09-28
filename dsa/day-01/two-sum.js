// brute force
function twoSum(nums, target) {
    const len = nums.length;
    for(let i=0;i<len;i++){
        for(let j=i+1;j<len;j++){
            if(nums[i] + nums[j] === target){
                return [i,j]
            }
        }
    }
}

// console.log(twoSum([2,7,11,15], 9));
// console.log(twoSum([3, 2, 4], 6));


// hashmap 
function twoSumOptimal(nums, target) {
    const seen = new Map();

    for(let i=0;i< nums.length;i++){
        const need = target - nums[i];
        if(seen.has(need)) {
            return [seen.get(need),i];
        }
        seen.set(nums[i],i);
    }
}

console.log(twoSumOptimal([2,7,11,15],9));
console.log(twoSumOptimal([3,2,4],6));