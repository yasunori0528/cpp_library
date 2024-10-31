# Card

`X` に `0` ~ `K` を代入した状態を `a` ~ `n` で保持しています．

例えば，`KnJ` は `KXJ|X=K` を表します．

## int_to_char

```cpp
char int_to_char(int x)
```

|引数|0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|返り値|`'0'`|`'1'`|`'2'`|`'3'`|`'4'`|`'5'`|`'6'`|`'7'`|`'8'`|`'9'`|`'T'`|`'J'`|`'Q'`|`'K'`|`'X'`|

表外の値を引数にとることはできません．

## char_to_int

```cpp
int char_to_int(char c)
```

|引数|`'0'`|`'1'`|`'2'`|`'3'`|`'4'`|`'5'`|`'6'`|`'7'`|`'8'`|`'9'`|`'T'`|`'J'`|`'Q'`|`'K'`|`'X'`|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|返り値|0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|

表外の値を引数にとることはできません．

## assign

```cpp
char assign(char &c)
```

`'a'` ~ `'n'` を `'0'` ~ `'K'` に変換します．

それ以外の値はそのまま返します．

## unassign

```cpp
char unassign(char &c)
```

`'a'` ~ `'n'` を `'X'` に変換します．

それ以外の値はそのまま返します．

## is_symbol

```cpp
bool is_symbol(char &c)
```

`c` = `'='`, `'*'`, `'^'` のとき `true` を返します．

それ以外のとき `false` を返します．

## is_joker

```cpp
bool is_joker(char &c)
```

`c` = `'X'`, `'a'` ~ `'n'` のとき `true` を返します．

それ以外のとき `false` を返します．

## int_to_str

```cpp
string int_to_str(bigint x)
```

数値を文字列に変換します．

`std::to_string(int x)` の多倍長整数バージョンです．

## str_to_int

```cpp
bigint str_to_int(string &s)
```

`0123456789TJQKabcdefghijklmn` からなる文字列を数値に変換します．

## print_str

```cpp
void print_str(string &s)
```

文字列を出力します．

`a` ~ `n` が含まれる場合，代入前の文字列と代入後の文字列を出力します．

### 例

```cpp
string s = "KnJ";
print_str(s);
```

出力

```
KXJ(KKJ)
```
