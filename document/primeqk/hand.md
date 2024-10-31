# hand

手札を管理する class です．

## メンバ変数

- `uint64_t data`
- `int sz`

### data

`data` を $16$ 進数で見たときの $i$ 桁目に，カード $i (=$ [`int_to_char(i)`](https://github.com/yasunori0528/cpp_library/blob/main/document/primeqk/card.md#int_to_char) $)$ の所持枚数を格納します．

- `'0'` もカードとして扱えます．
- 各カードにつき，管理できるのは $15$ 枚までです．

### sz

手札の枚数です．

## コンストラクタ

```cpp
(1) hand h()
(2) hand h(string &s)
```

- (1) 空手札を作ります．
- (2) `s` からなる手札を作ります．

## get_data

```cpp
uint64_t h.get_data()
```

`data` を取得します．

## size
```cpp
int h.size()
```

`sz` を取得します．

## count

```cpp
int h.count(int x)
int h.count(char c)
```

カードの枚数を取得します．

## contain

```cpp
bool h.contain(string &s)
```

`h` に `s` が含まれているとき `true` を返します．

`s` に 演算子 `'='`, `'*'`, `'^'` が含まれていても問題ないです．

## draw

```cpp
void h.draw(int x)
void h.draw(char c)
```

カードを1枚手札に加えます．

> [!WARNING]
>
> オーバーフローしたときの動作は未定義です．
>
> 必要であれば `count` 等で確認してください．

## discard

```cpp
void h.discard(int x)
void h.discard(char c)
```

カードを1枚手札から取り除きます．

> [!WARNING]
>
> オーバーフローしたときの動作は未定義です．
>
> 必要であれば `count` 等で確認してください．

## play

```cpp
void h.play(string &s)
```

`h` から `s` を出します．

`s` に 演算子 `'='`, `'*'`, `'^'` が含まれていても問題ないです．

> [!WARNING]
>
> オーバーフローしたときの動作は未定義です．
>
> 必要であれば `contain` 等で確認してください．

## div25

```cpp
bool h.div25()
```

`h` に $2$ か $5$ で割り切れるカードしかないとき， `true` を返します．

## mod3

```cpp
int h.mod3()
```

`h` を $3$ で割った余りを返します．

`'X'` が $1$ 枚以上含まれているときは， $-1$ を返します．

## mod11

```cpp
int h.mod11()
```

`h` を $11$ で割った余りを返します．

`'0'` ~ `'9'`, `'X'` が $1$ 枚以上含まれているときは， `-1` を返します．


## max_natural

`h` で作ることのできる最大の自然数を返します．

## print

`h` に含まれるカードを出力します．
