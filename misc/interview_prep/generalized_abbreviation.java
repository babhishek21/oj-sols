/**
 * Generalized Abbreviation (Leetcode)
 * For example for the word "word"
 * f(word) would return: [word, 1ord, w1rd, wo1d, wor1, 2rd, w2d, wo2, 1o1d, 1or1, w1r1, 1o2, 2r1, 3d, w3, 4]
 */

import java.io.*;
import java.util.*;

public class generalized_abbreviation {
  private static void printArrayList(List<String> list) {
    System.out.println("[ " + String.join(", ", list) + " ]"); // JAVA 8 only
  }

  public static void main(String[] args) {

    System.out.println("Testing Generalized Abbreviations by Backtracking:");

    System.out.print("\nAbbreviations for \"word\": ");
    printArrayList(gaBacktrack.generateAbbreviations("word"));

    System.out.print("\nAbbreviations for \"apple\": ");
    printArrayList(gaBacktrack.generateAbbreviations("apple"));

    System.out.println("\nTesting Generalized Abbreviations by Divide and Conquer:");

    System.out.print("\nAbbreviations for \"word\": ");
    printArrayList(gaDAC.generateAbbreviations("word"));

    System.out.print("\nAbbreviations for \"apple\": ");
    printArrayList(gaDAC.generateAbbreviations("apple"));
  }
}

/**
 * Method 1. Backtracking
 */
class gaBacktrack {
  public static List<String> generateAbbreviations(String word) {
    List<String> result = new ArrayList<>();
    helper(word, "", 0, result, false);
    return result;
  }

  // isPrefixAbbr: true => Prefix is abbreviation. Hence can only add alphabets
  // isPrefixAbbr: false -> Prefix is not an abbreviation at the end. Can add both numbers and alphabets
  private static void helper(String word, String prefix, int start, List<String> result, boolean isPrefixAbbr) {
    if(start == word.length()) {
      result.add(prefix);
      return;
    }

    if(!isPrefixAbbr)
      for(int end = start+1; end <= word.length(); end++)
        helper(word, prefix + Integer.toString(end-start), end, result, true);

    helper(word, prefix + word.charAt(start), start+1, result, false);
  }
}

/**
 * 2. Divide and Conquer
 */
class gaDAC {
  public static List<String> generateAbbreviations(String word) {
    Set<String> temp = helper(word);
    List<String> result = new ArrayList<>(temp);
    Collections.sort(result); // not necessary, just for generalized_abbreviationing
    return result;
  }

  public static Set<String> helper(String word) {
    int n = word.length();
    Set<String> res = new HashSet<>();

    if(word.isEmpty()) {
      res.add("");
      return res;
    }

    res.add(Integer.toString(n));
    for(int i=0; i<n; i++) {
      Set<String> left = helper(word.substring(0, i));
      Set<String> right = helper(word.substring(i+1));

      for(String leftstr: left)
        for(String rightstr: right)
          res.add(leftstr + word.charAt(i) + rightstr);
    }

    return res;
  }
}
