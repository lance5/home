#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode( int x ) : val( x ), next( nullptr ) {}
};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int nSize = nums.size();
		for (int i = 0; i < nSize; ++i)
		{
			for (int j = i + 1; j < nSize; ++j)
			{
				int nTarget = nums[i] + nums[j];
				if (target == nTarget)
				{
					return vector<int>{ i, j };
				}
			}
		}
	}

	ListNode* addTwoNumbers( ListNode* l1, ListNode* l2 ) {
		int sum = 0;
		ListNode* pParte = nullptr;
		ListNode* pTem = pParte;
		while (l1 || l2)
		{
			int i1 = l1 ? l1->val : 0;
			int i2 = l2 ? l2->val : 0;
			sum = i1 + i2 + sum / 10;
			if (!pParte)
			{
				pTem = new ListNode( sum % 10 );
				pParte = pTem;
			}
			else
			{
				pTem = pTem->next = new ListNode( sum % 10 );
			}
			l1 = l1 ? l1->next : nullptr;
			l2 = l2 ? l2->next : nullptr;
		}

		if (sum >= 10)
		{
			sum = sum / 10;
			pTem->next = new ListNode( sum % 10 );
		}
		return pParte;
	}

	int lengthOfLongestSubstring( string s ) {
#define MAX(a, b) (a>b?a:b)
		bool ExistChar[256] = { false };
		int nLen = s.length();
		int j = 0;
		int i = 0;
		int nMaxLen = 0;
		while (j < nLen )
		{
			if(ExistChar[s[j]])
			{
				nMaxLen = MAX( nMaxLen , j - i );
				while (s[j] != s[i])
				{
					ExistChar[s[i]] = false;
					++i;
				}
				++i;
			}
			else
			{
				ExistChar[s[j]] = true;
			}
			++j;
		}
		nMaxLen = MAX( nMaxLen, j - i );
		return nMaxLen;
	}

	double findMedianSortedArrays( vector<int>& nums1, vector<int>& nums2 ) {
		int nNum1Start = 0;
		int nNum2Start = 0;
		int nLastNum = 0;
		const int nSize = nums1.size() + nums2.size();
		const int nMiddle = (int)(nSize / 2) + 1;
		int nCurNum = 0;
		for ( int i = 0; i < nMiddle; ++i )
		{
			if( nNum1Start == nums1.size() && nNum2Start == nums2.size() )
				break;
			if(nNum1Start == nums1.size())
				nCurNum = nums2[nNum2Start++];
			else if(nNum2Start == nums2.size())
				nCurNum = nums1[nNum1Start++];
			else
			{
				if (nums1[nNum1Start] > nums2[nNum2Start])
					nCurNum = nums2[nNum2Start++];
				else
					nCurNum = nums1[nNum1Start++];
			}

			if( i != nMiddle - 1 )
				nLastNum = nCurNum;
		}
		if( nSize % 2 )
			return nCurNum;
		else 
			return ( (double)nCurNum + (double)nLastNum ) / 2.0f;
	}

	string longestPalindrome( string s ) {
		/*int nTempSize = s.size() * 2 + 2;
		char* aTemp = new char[nTempSize];
		int a
		aTemp[nTempSize - 1] = '\0';
		const char cBlock = '#';
		for( int i = 0; i < nTempSize - 1; ++i )
		{
			if( i % 2 )
				aTemp[i] = s[i / 2];
			else
				aTemp[i] = cBlock;
		}



		delete[] aTemp;
		return "";*/
	}
};