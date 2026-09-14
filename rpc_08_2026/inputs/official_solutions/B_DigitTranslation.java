// Arup Guha
// 3/7/2024
// Solution to 2023/4 NAQ Problem B: Digit Translation

import java.util.*;
import java.io.*;

public class b {

	final public static String[] NUMS = {"zero","one","two","three","four","five",
										 "six","seven","eight","nine"};
										 
	final public static int MOD = 9302023;
										 
	public static void main(String[] args) throws Exception {
	
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = stdin.readLine().toCharArray();
		int n = s.length;
		
		// Set up both DP arrays, one for shortest length, other for total number of
		// strings of that length.
		int[] dplen = new int[n+1];
		int[] dpcnt = new int[n+1];
		dplen[0] = 0;
		dpcnt[0] = 1;

		// Loop through letters in string.
		for (int i=0; i<n; i++) {
			
			// Answer by adding this character and not doing a substitution.
			int bestLen = dplen[i]+1;
			int bestCnt = dpcnt[i];
			
			// Try each string here.
			for (String num: NUMS) {
				
				// Avoid AOOB.
				int nLen = num.length();
				if (nLen > i+1) continue;
			
				if (!match(num, s, i-nLen+1)) continue;
				
				int altLen = dplen[i-nLen+1] + 1;
				
				// Strictly better, update both.
				if (altLen < bestLen) {
					bestLen = altLen;
					bestCnt = dpcnt[i-nLen+1];
				}
				
				// Equal case, add solutions.
				else if (altLen == bestLen) {
					bestCnt = (bestCnt + dpcnt[i-nLen+1])%MOD;
				}
			}
			
			// Store.
			dplen[i+1] = bestLen;
			dpcnt[i+1] = bestCnt;
		}
		
		// Ta da!
		System.out.println(dplen[n]);
		System.out.println(dpcnt[n]);
	}
	
	// Returns true
	public static boolean match(String pattern, char[] text, int sI) {
		for (int i=sI; i<sI+pattern.length(); i++)
			if (text[i] != pattern.charAt(i-sI))
				return false;
		return true;
	}
}
