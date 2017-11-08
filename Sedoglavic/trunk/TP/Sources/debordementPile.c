#include <stdio.h>

void function(){

  int foo = 0 ;
  int *ret ;

  ret = &foo + 2;
  (*ret) += 7 ;
}

int main(void){

  int x = 0 ;
  function () ;
  x = 1 ;
  printf("%d\n",x) ;
  return 0 ;
}

/*
[sedoglav@erichtonios sedoglav]$ gcc -g debordementPile.c
[sedoglav@erichtonios sedoglav]$ gdb a.out 
GNU gdb 5.2.1-2mdk (Mandrake Linux)
Copyright 2002 Free Software Foundation, Inc.
GDB is free software, covered by the GNU General Public License, and you are
welcome to change it and/or distribute copies of it under certain conditions.
Type "show copying" to see the conditions.
There is absolutely no warranty for GDB.  Type "show warranty" for details.
This GDB was configured as "i586-mandrake-linux-gnu"...
(gdb) break main
Breakpoint 1 at 0x8048372: file debordementPile.c, line 14.
(gdb) ru
Starting program: /home/sedoglav/a.out 

Breakpoint 1, main () at debordementPile.c:14
14        int x = 0 ;
(gdb) disassemble
Dump of assembler code for function main:
0x8048362 <main>:       push   %ebp
0x8048363 <main+1>:     mov    %esp,%ebp
0x8048365 <main+3>:     sub    $0x8,%esp
0x8048368 <main+6>:     and    $0xfffffff0,%esp
0x804836b <main+9>:     mov    $0x0,%eax
0x8048370 <main+14>:    sub    %eax,%esp
0x8048372 <main+16>:    movl   $0x0,0xfffffffc(%ebp)
0x8048379 <main+23>:    call   0x804833c <function>
0x804837e <main+28>:    movl   $0x1,0xfffffffc(%ebp)
0x8048385 <main+35>:    sub    $0x8,%esp
0x8048388 <main+38>:    pushl  0xfffffffc(%ebp)
0x804838b <main+41>:    push   $0x80483e8
0x8048390 <main+46>:    call   0x8048268 <printf>
0x8048395 <main+51>:    add    $0x10,%esp
0x8048398 <main+54>:    mov    $0x0,%eax
0x804839d <main+59>:    leave  
0x804839e <main+60>:    ret    
End of assembler dump.
(gdb) s
16        function () ;
(gdb) s
function () at debordementPile.c:3
3       void function(){
(gdb) s
5         int foo = 0 ;
(gdb) s
8         ret = &foo + 1;
(gdb) s
9         (*ret) += 7 ;
(gdb) printf "%x",*ret
804837e(gdb) s
10      }
(gdb) printf "%x",*ret
8048385(gdb) s
main () at debordementPile.c:18
18        printf("%d\n",x) ;
(gdb) s
0
19        return 0 ;
(gdb) s
20      }
(gdb) s
0x40038082 in __libc_start_main () from /lib/i686/libc.so.6
(gdb) s
Single stepping until exit from function __libc_start_main, 
which has no line number information.

Program exited normally.

*/
 
