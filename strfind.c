#include <stdio.h>
#include <assert.h>

unsigned search(char *s, unsigned len) {
  if (len<3)
    return len; // not found
  unsigned seen=0;
  for (unsigned i=0; i<len; i++) {
    char ch=s[i];                 // других чтений s[...] не должно быть
    if (seen==0 && ch=='+')
            seen=1;
    else if (seen==1 && ch=='+')
            seen=2;
    else if (seen==2 && ch=='+') 
            seen=2;              
    else if (seen==2 && ch=='x')
            return i-2;  // found
    else
            seen=0;    // reset
  }
  return len;                // not found
}

unsigned naive_search(const char *s, unsigned len) {
  for (unsigned i = 0; i + 2 < len; i++) {
    if (s[i] == '+' && s[i + 1] == '+' && s[i + 2] == 'x') {
      return i;
    }
  }
  return len;
}

int main() {
  char s[LEN];
  assert(search(s, LEN) == naive_search(s, LEN));
  //TODO: здесь нужно написать свои ограничения, которые гарантируют следующее:
  //TODO: функция `search(s, len)` возвращает индекс в `s` начала подстроки `++x`, если эта подстрока есть в строке `s`, иначе возвращает `len`
  //TODO: подсказка: напишите вспомогательную неоптимальную функцию для этой же задачи
  return 0;
}

// ~/Study/mathlog/cbmc-2026 master* ❯ cbmc --trace strfind.c -DLEN=10 --unwind 12 > res
// ~/Study/mathlog/cbmc-2026 master* ❯ cat res
// ...
// State 11 file strfind.c function main line 32 thread 0
// ----------------------------------------------------
//   e={ '+', '+', '+', 'x', '(', '+', '+', 'x', '(', ';' } ({ 00101011, 00101011, 00101011, 01111000, 00101000, 00101011, 00101011, 01111000, 00101000, 00111011 })
// ...
// State 92 file strfind.c function main line 35 thread 0
// ----------------------------------------------------
//   return_value_search=5u (00000000 00000000 00000000 00000101)
// ...
// State 109 file strfind.c function main line 35 thread 0
// ----------------------------------------------------
//   return_value_naive_search=1u (00000000 00000000 00000000 00000001)
//