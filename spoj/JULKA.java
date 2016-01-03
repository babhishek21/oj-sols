import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

public class Main
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc = new Scanner(System.in);
		
		for(int i=0; i<10; i++) {
			BigInteger apples = sc.nextBigInteger();
			BigInteger diff = sc.nextBigInteger();
			
			BigInteger temp = apples.subtract(diff);
			temp = temp.divide(BigInteger.valueOf(2));
			
			System.out.println(temp.add(diff));
			System.out.println(temp);
		}
	}
}