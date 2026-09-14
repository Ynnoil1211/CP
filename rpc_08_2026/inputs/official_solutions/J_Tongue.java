// Arup Guha
// 3/11/2024
// Solution to 2023/4 NAQ Problem J: Tip of your Tongue

import java.util.*;
import java.io.*;

public class j {

	public static void main(String[] args) throws Exception {
		
		// Set two primes for hashing.
		long[] primes = new long[2];
		long x = 1000001001;
		int idx = 0;
		while (idx<2) {
			if (isprime(x)) 
				primes[idx++] = x;
			x+=2;
		}
	
		FastScanner stdin = new FastScanner(System.in);
		
		int nW = stdin.nextInt();
		int nQ = stdin.nextInt();
		
		// Read words.
		int maxlen = 0;
		char[][] words = new char[nW][];
		for (int i=0; i<nW; i++) {
			words[i] = stdin.next().toCharArray();
			maxlen = Math.max(maxlen, words[i].length);
		}
		
		// Create my three hashmaps.
		HashMap<Long,Integer>[] pre = new HashMap[maxlen];
		HashMap<Long,Integer>[] suf = new HashMap[maxlen];
		HashMap<Long,Integer>[] and = new HashMap[maxlen];
		for (int i=0; i<maxlen; i++) {
			pre[i] = new HashMap<Long,Integer>();
			suf[i] = new HashMap<Long,Integer>();
			and[i] = new HashMap<Long,Integer>();
		}
		
		// Build pow 29.
		long[][] pow29 = new long[2][maxlen+1];
		pow29[0][0] = 1; pow29[1][0] = 1;
		for (int i=1; i<=maxlen; i++) 
			for (int k=0; k<2; k++)
				pow29[k][i] = (pow29[k][i-1]*29)%primes[k];
		
		// Add each word.
		for (int i=0; i<nW; i++) {
			
			long[] hpre = new long[2];
			long[] hsuf = new long[2];
			long[] hand = new long[2];
			
			// Go through each letter.
			int n = words[i].length;
			for (int j=0; j<n; j++) {
				
				// Update hash.
				for (int k=0; k<2; k++) {
					hpre[k] = (29*hpre[k]+1+words[i][j]-'a')%primes[k];
					hsuf[k] = (29*hsuf[k]+1+words[i][n-1-j]-'a')%primes[k];
					hand[k] = (hpre[k]*pow29[k][j+1]+hsuf[k])%primes[k];
				}
				
				// Calculate three keys for three hash tables.
				long key1 = (hpre[0]<<31) + hpre[1];
				long key2 = (hsuf[0]<<31) + hsuf[1];
				long key3 = (hand[0]<<31) + hand[1];
				
				// See if we've used these before.
				if (!pre[j].containsKey(key1)) pre[j].put(key1, 0);
				if (!suf[j].containsKey(key2)) suf[j].put(key2, 0);
				if (!and[j].containsKey(key3)) and[j].put(key3, 0);
				
				// Update the times we've seen each hash.
				pre[j].put(key1, pre[j].get(key1)+1);
				suf[j].put(key2, suf[j].get(key2)+1);
				and[j].put(key3, and[j].get(key3)+1);
			}
		}
		
		// Answer queries.
		StringBuffer sb = new StringBuffer();
		for (int i=0; i<nQ; i++) {
			
			String type = stdin.next();
			char[] w1 = stdin.next().toCharArray();
			char[] w2 = stdin.next().toCharArray();
			
			long[] hpre = new long[2];
			long[] hsuf = new long[2];
			long[] hand = new long[2];
			
			// Go through each letter.
			int n = w1.length;
			
			// Tricky to avoid run time error.
			if (n > maxlen) {
				sb.append(0+"\n");
				continue;
			}
			
			// Go through each letter to calculate hash.
			for (int j=0; j<n; j++) {
				
				// Update hash.
				for (int k=0; k<2; k++) {
					hpre[k] = (29*hpre[k]+1+w1[j]-'a')%primes[k];
					hsuf[k] = (29*hsuf[k]+1+w2[n-1-j]-'a')%primes[k];
					hand[k] = (hpre[k]*pow29[k][j+1]+hsuf[k])%primes[k];
				}
			}
			
			// Get the corresponding keys.
			long key1 = (hpre[0]<<31) + hpre[1];
			long key2 = (hsuf[0]<<31) + hsuf[1];
			long key3 = (hand[0]<<31) + hand[1];
			
			// Just solve all three of these.
			int a1 = 0, a2 = 0, a3 = 0;
			if (pre[n-1].containsKey(key1)) a1 = pre[n-1].get(key1);
			if (suf[n-1].containsKey(key2)) a2 = suf[n-1].get(key2);
			if (and[n-1].containsKey(key3)) a3 = and[n-1].get(key3);
			
			// Answer appropriate query.
			if (type.equals("AND")) 
				sb.append(a3+"\n");
			else if (type.equals("OR")) 
				sb.append( (a1+a2-a3)+"\n");
			else 
				sb.append( (a1+a2-2*a3)+"\n");
		}
		
		// Ta da!
		System.out.print(sb);
	}
	
	public static boolean isprime(long n) {
		for (int i=2; i*i<=n; i++)
			if (n%i == 0)
				return false;
		return true;
	}
}

class FastScanner {
	
    BufferedReader br;
    StringTokenizer st;
	
    public FastScanner(InputStream i) {
        br = new BufferedReader(new InputStreamReader(i));
        st = new StringTokenizer("");
    }
			
    public String next() throws IOException {
        if(st.hasMoreTokens())
            return st.nextToken();
        else
            st = new StringTokenizer(br.readLine());
        return next();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    
    public long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    public double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
    
}
