# Markov Algorithm Online Solver

https://mao.snuke.org/ の問題をコードを全探索して解くことを目指しています。

それぞれの長さのコードを全て生成し、与えたサンプルが通るかどうかを判定します。コロン（`:`）と改行を除いて、10文字ちょっとくらいまでならば解けます。文字列長の短い順に探索し、これまでよりも行数が短ければ出力します。アルファベットサイズ（入出力に現われない文字を何種類使うか）は人が決める必要があります。

## 入力フォーマット

標準入力から入力します。

```
最大ステップ数
最大文字列長
アルファベットサイズ（使用する文字の種類数）
文字1
文字2
 :
サンプル数
サンプル1入力:サンプル1出力
サンプル2入力:サンプル2出力
 :
```

## 入出力例

### Hello, World!

https://mao.snuke.org/tasks/1

```
16
16
2
Hello,
World!
1
Hello,:World!
```

```
Max step: 16
Max length: 16
Alphabet: Hello, World!
Samples:
  Hello, -> World!
Length: 1
Length: 2
!!! Found 2 lines solution
Hello,:
::World!
!!! Found 1 lines solution
Hello,:World!
Length: 3
Length: 4
Length: 5
Length: 6
```

### Append s

https://mao.snuke.org/tasks/8

```
16
16
2
b
s
6
:s
b:bs
bb:bbs
bbb:bbbs
bbbb:bbbbs
bbbbb:bbbbbs
```

```
Max step: 16
Max length: 16
Alphabet: b s
Samples:
   -> s
  b -> bs
  bb -> bbs
  bbb -> bbbs
  bbbb -> bbbbs
  bbbbb -> bbbbbs
Length: 1
Length: 2
Length: 3
Length: 4
Length: 5
Length: 6
Length: 7
!!! Found 3 lines solution
sb:bs
s::
:ss
Length: 8
Length: 9
```

### Flip

https://mao.snuke.org/tasks/9

```
8
8
3
0
1
2
7
0:1
1:0
00:11
01:10
10:01
11:00
00101:11010
```

```
Max step: 8
Max length: 8
Alphabet: 0 1 2
Samples:
  0 -> 1
  1 -> 0
  00 -> 11
  01 -> 10
  10 -> 01
  11 -> 00
  00101 -> 11010
Length: 1
Length: 2
Length: 3
Length: 4
Length: 5
Length: 6
Length: 7
Length: 8
Length: 9
Length: 10
!!! Found 4 lines solution
20:12
21:02
2::
:2
Length: 11
```
