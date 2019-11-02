#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays();

int main() {
	int arr1[255], arr2[255], size1, size2;
	scanf("%d", &size1);
	for(int i=0;i<size1;i++) scanf("%d", arr1+i);
	scanf("%d", &size2);
	for(int i=0;i<size2;i++) scanf("%d", arr2+i);
	printf("%lf\n", findMedianSortedArrays(arr1, size1, arr2, size2));
	return 0;
}



double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int totalSize = nums1Size + nums2Size;
    int *temp = (int *)malloc((sizeof(int)) * (totalSize + 2));
    int temptop = 0, i = 0, j = 0;
    double ret;
    while(temptop < totalSize) {
        if(temptop == ((int)(totalSize / 2) + 1)) { break;}
        if((i == nums1Size) || ((j != nums2Size) && (nums1[i] >= nums2[j]))) {temp[temptop++] = nums2[j++];continue;}
        if((j == nums2Size) || ((i != nums1Size) && (nums1[i] < nums2[j]))) {temp[temptop++] = nums1[i++];continue;}
    }
    if((totalSize % 2) == 0) {
        ret = (temp[--temptop] + temp[--temptop]) / 2.0;
    } else {
        ret = temp[--temptop];
    }
    free(temp);
    return ret;
}

