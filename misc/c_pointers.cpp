/**
 * Pointers in C/C++
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  char    abc[27];
  char    *ptr = abc;
  strcpy(abc, "abcdefgxyz");
   /*
   * What are the types and values of expressions:
   *

   * 1. abc
   * 2. *abc
   * 3. abc[2]
   * 4. &abc[3] //&abc[3] = abc + 3*sizeof(char)
   * 5. abc+4
   * 6. *(abc+5) + 20000  //h  long long x = int * 1LL * int
   * 7. abc[10] //'\0'
   * 8. abc[12] //memset ()
   * 9. &ptr //char**
   */

  // cout << abc << " " << typeid(abc).name() << endl;
  // cout << *abc << " " << typeid(*abc).name() << endl;

  printf("%d\n", abc);    // constant pointer to first element of char array abc[] i.e. it is pointer to &abc[0]. Stores the address.
  printf("%d\n", *abc);   // dereferences the pointer, gives the actual character
  printf("%d\n", &abc);   // alias/address of pointer abc (gives the address of abc[0]). WIERD!!!

  printf("%d\n", abc[2]);   // [] dereferences the address (abc+2)
  printf("%d\n", *(abc+2)); // same as above

  printf("%d\n", &abc[3]);  // [] dereferences the address (abc+3), then & gives the address of that element. so equals (abc + 3*sizeof(char))

  printf("%d\n", abc+4);  // abc + 4 == address of the fifth element of the array abc[]

  printf("%d\n", *(abc+5) + 20000); // *(abc + 4) == (char)(102) == (int)('f'). Add 20000 to that.
  printf("%c\n", *(abc+5) + 20000); // as a character, it's unicode å

  printf("%d\n", abc[10]); // the null character '\0' string terminating character

  printf("%d\n", abc[12]); // tries to dereference allocated but uninitialised memory. Indeterminate value unless global

  printf("%d\n", ptr);   // printf automatically gives what's stored in a normal pointer. ptr points to same address as pointer abc
  printf("%d\n", abc);   // Since this is special cosnt pointer to first array element, it is ptr == abc == &abc[0]
  printf("%d\n", *ptr);  // dereference the pointer to give character 'a'
  printf("%d\n", &ptr);  // address of the pointer ptr which is points to same address as pointer abc. So actual address where the pointer ptr is stored, which is not the same as the address stored in ptr

  /*************************************************************************/
  int lol[20] = {10,11,55,12,2,15,45,452,1545,1515,12,12,1,121,63,};
  int *haha = lol;

  printf("\n%d\n", sizeof(int));
  printf("%d\n", sizeof(lol));    // 20 * sizeof(int)

  printf("%d\n", sizeof(int*));   // size of pointers
  printf("%d\n", sizeof(&lol));
  printf("%d\n", sizeof(haha));

  printf("%d\n", lol);            // lol = &lol[0]
  printf("%d\n", haha);           // haha = lol
  printf("%d\n", *haha);          // *haha = *(&lol[0]) = lol[0] = 10
  printf("%d\n", lol+2);          // lol + 2 = &lol[2]
  printf("%d\n", haha+2);         // haha + 2 = &haha[2] = &lol[2]
  printf("%d\n", &lol[2]);        // &lol[2] = &lol + 2*sizeof(int)
  printf("%d\n", &haha[2]);       // &haha[2] = &lol[2]
  printf("%d\n", *(lol+2));       // *(lol+2) = *(&lol + 2*sizeof(int)) = *(&lol[2]) = lol[2] = 55
  printf("%d\n", *(haha+2));      // *(haha+2) = *(lol+2)

  printf("%d\n", &lol);             // &lol = lol
  printf("%d\n", (&lol) + 2);       // &lol + 2*sizeof(lol)
  printf("%d\n", &haha);            // &haha != &lol
  printf("%d\n", (&haha) + 2);      // &haha + 2*sizeof(int*)

  return 0;
}
