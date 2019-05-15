### Lex result

```
< 1 , int >
< 3 , a >
< 4 , ; >
< 1 , int >
< 3 , b >
< 4 , ; >
< 1 , int >
< 3 , c >
< 4 , ; >
< 3 , a >
< 4 , = >
< 2 , 2 >
< 4 , ; >
< 3 , b >
< 4 , = >
< 2 , 1 >
< 4 , ; >
< 1 , if >
< 4 , ( >
< 3 , a >
< 4 , > >
< 3 , b >
< 4 , ) >
< 3 , c >
< 4 , = >
< 3 , a >
< 4 , + >
< 3 , b >
< 4 , ; >
< 1 , else >
< 3 , c >
< 4 , = >
< 3 , a >
< 4 , - >
< 3 , b >
< 4 , ; >
```
-----Lex result END-----

### Grammar Analysis
#### First Table
| First |  |
|---|---|
| < 6 , C > | < 2,  > < 3,  > < 4, ( > |
| < 6 , D > | < 1, float > < 1, int > < 7,  > |
| < 6 , E > | < 2,  > < 3,  > < 4, ( > |
| < 6 , F > | < 2,  > < 3,  > < 4, ( > |
| < 6 , L > | < 1, float > < 1, int > |
| < 6 , M > | < 7,  > |
| < 6 , N > | < 7,  > |
| < 6 , P > | < 7,  > |
| < 6 , Q1 > | < 7,  > |
| < 6 , Q2 > | < 7,  > |
| < 6 , S > | < 1, if > < 1, while > < 3,  > |
| < 6 , T > | < 2,  > < 3,  > < 4, ( > |
#### Follow Table
| Follow |  |
|---|---|
| < 6 , C > | < 4, ) > |
| < 6 , D > | < 1, if > < 1, while > < 3,  > |
| < 6 , E > | < 4, ) > < 4, + > < 4, - > < 4, ; > < 4, < > < 4, == > < 4, > > |
| < 6 , F > | < 4, ) > < 4, * > < 4, + > < 4, - > < 4, / > < 4, ; > < 4, < > < 4, == > < 4, > > |
| < 6 , L > | < 3,  > |
| < 6 , M > | < 1, if > < 1, while > < 3,  > < 4, ( > |
| < 6 , N > | < 1, else > |
| < 6 , P > | < 5, $ > |
| < 6 , Q1 > | < 1, float > < 1, if > < 1, int > < 1, while > < 3,  > |
| < 6 , Q2 > | < 1, float > < 1, if > < 1, int > < 1, while > < 3,  > |
| < 6 , S > | < 1, else > < 1, if > < 1, while > < 3,  > < 5, $ > |
| < 6 , T > | < 4, ) > < 4, * > < 4, + > < 4, - > < 4, / > < 4, ; > < 4, < > < 4, == > < 4, > > |
#### Grammar Table
| # | Left | Right |
|---|---|---|
| 0 | < 6 , P > | < 6, Q1 > < 6, D > < 6, S > |
| 1 | < 6 , Q1 > | < 7,  > |
| 2 | < 6 , D > | < 6, L > < 3,  > < 4, ; > < 6, Q2 > < 6, D > |
| 3 | < 6 , D > | < 7,  > |
| 4 | < 6 , Q2 > | < 7,  > |
| 5 | < 6 , L > | < 1, int > |
| 6 | < 6 , L > | < 1, float > |
| 7 | < 6 , S > | < 3,  > < 4, = > < 6, E > < 4, ; > |
| 8 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |
| 9 | < 6 , S > | < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |
| 10 | < 6 , S > | < 6, S > < 6, M > < 6, S > |
| 11 | < 6 , C > | < 6, E > < 4, < > < 6, E > |
| 12 | < 6 , C > | < 6, E > < 4, > > < 6, E > |
| 13 | < 6 , C > | < 6, E > < 4, == > < 6, E > |
| 14 | < 6 , E > | < 6, E > < 4, + > < 6, T > |
| 15 | < 6 , E > | < 6, E > < 4, - > < 6, T > |
| 16 | < 6 , E > | < 6, T > |
| 17 | < 6 , T > | < 6, F > |
| 18 | < 6 , T > | < 6, T > < 4, * > < 6, F > |
| 19 | < 6 , T > | < 6, T > < 4, / > < 6, F > |
| 20 | < 6 , F > | < 4, ( > < 6, E > < 4, ) > |
| 21 | < 6 , F > | < 3,  > |
| 22 | < 6 , F > | < 2,  > |
| 23 | < 6 , M > | < 7,  > |
| 24 | < 6 , N > | < 7,  > |
#### Transfer Machine
| Status:56 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 1 | < 6 , S > | < 6, S >. < 6, M > < 6, S > |
| 10 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S >. |

| Status:55 | Left | Right |
|---|---|---|
| 0 | < 6 , S > |. < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 3,  > < 4, = > < 6, E > < 4, ; > |
| 0 | < 6 , S > |. < 6, S > < 6, M > < 6, S > |
| 9 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M >. < 6, S > |

| Status:54 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 8 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else >. < 6, M > < 6, S > |

| Status:53 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 1 | < 6 , S > | < 6, S >. < 6, M > < 6, S > |
| 7 | < 6 , S > | < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S >. |

| Status:52 | Left | Right |
|---|---|---|
| 7 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N >. < 1, else > < 6, M > < 6, S > |

| Status:51 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 0 | < 6 , N > |. < 7,  > |
| 1 | < 6 , S > | < 6, S >. < 6, M > < 6, S > |
| 6 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S >. < 6, N > < 1, else > < 6, M > < 6, S > |

| Status:50 | Left | Right |
|---|---|---|
| 0 | < 6 , S > |. < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 3,  > < 4, = > < 6, E > < 4, ; > |
| 0 | < 6 , S > |. < 6, S > < 6, M > < 6, S > |
| 6 | < 6 , S > | < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M >. < 6, S > |

| Status:49 | Left | Right |
|---|---|---|
| 1 | < 6 , T > | < 6, T >. < 4, * > < 6, F > |
| 1 | < 6 , T > | < 6, T >. < 4, / > < 6, F > |
| 3 | < 6 , E > | < 6, E > < 4, + > < 6, T >. |

| Status:48 | Left | Right |
|---|---|---|
| 1 | < 6 , T > | < 6, T >. < 4, * > < 6, F > |
| 1 | < 6 , T > | < 6, T >. < 4, / > < 6, F > |
| 3 | < 6 , E > | < 6, E > < 4, - > < 6, T >. |

| Status:47 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 5 | < 6 , S > | < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) >. < 6, M > < 6, S > |

| Status:46 | Left | Right |
|---|---|---|
| 0 | < 6 , S > |. < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 3,  > < 4, = > < 6, E > < 4, ; > |
| 0 | < 6 , S > |. < 6, S > < 6, M > < 6, S > |
| 5 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M >. < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |

| Status:45 | Left | Right |
|---|---|---|
| 3 | < 6 , F > | < 4, ( > < 6, E > < 4, ) >. |

| Status:44 | Left | Right |
|---|---|---|
| 3 | < 6 , T > | < 6, T > < 4, * > < 6, F >. |

| Status:43 | Left | Right |
|---|---|---|
| 3 | < 6 , T > | < 6, T > < 4, / > < 6, F >. |

| Status:42 | Left | Right |
|---|---|---|
| 1 | < 6 , E > | < 6, E >. < 4, + > < 6, T > |
| 1 | < 6 , E > | < 6, E >. < 4, - > < 6, T > |
| 3 | < 6 , C > | < 6, E > < 4, < > < 6, E >. |

| Status:41 | Left | Right |
|---|---|---|
| 1 | < 6 , E > | < 6, E >. < 4, + > < 6, T > |
| 1 | < 6 , E > | < 6, E >. < 4, - > < 6, T > |
| 3 | < 6 , C > | < 6, E > < 4, == > < 6, E >. |

| Status:40 | Left | Right |
|---|---|---|
| 1 | < 6 , E > | < 6, E >. < 4, + > < 6, T > |
| 1 | < 6 , E > | < 6, E >. < 4, - > < 6, T > |
| 3 | < 6 , C > | < 6, E > < 4, > > < 6, E >. |

| Status:39 | Left | Right |
|---|---|---|
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , C > | < 6, E > < 4, > >. < 6, E > |

| Status:38 | Left | Right |
|---|---|---|
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , C > | < 6, E > < 4, == >. < 6, E > |

| Status:37 | Left | Right |
|---|---|---|
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , C > | < 6, E > < 4, < >. < 6, E > |

| Status:36 | Left | Right |
|---|---|---|
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 2 | < 6 , T > | < 6, T > < 4, / >. < 6, F > |

| Status:35 | Left | Right |
|---|---|---|
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 2 | < 6 , T > | < 6, T > < 4, * >. < 6, F > |

| Status:34 | Left | Right |
|---|---|---|
| 1 | < 6 , E > | < 6, E >. < 4, + > < 6, T > |
| 1 | < 6 , E > | < 6, E >. < 4, - > < 6, T > |
| 2 | < 6 , F > | < 4, ( > < 6, E >. < 4, ) > |

| Status:33 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 4 | < 6 , S > | < 1, if > < 4, ( > < 6, C > < 4, ) >. < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |

| Status:32 | Left | Right |
|---|---|---|
| 4 | < 6 , S > | < 1, while > < 6, M > < 4, ( > < 6, C >. < 4, ) > < 6, M > < 6, S > |

| Status:31 | Left | Right |
|---|---|---|
| 4 | < 6 , S > | < 3,  > < 4, = > < 6, E > < 4, ; >. |

| Status:30 | Left | Right |
|---|---|---|
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , E > | < 6, E > < 4, - >. < 6, T > |

| Status:29 | Left | Right |
|---|---|---|
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , E > | < 6, E > < 4, + >. < 6, T > |

| Status:28 | Left | Right |
|---|---|---|
| 5 | < 6 , D > | < 6, L > < 3,  > < 4, ; > < 6, Q2 > < 6, D >. |

| Status:27 | Left | Right |
|---|---|---|
| 0 | < 6 , D > |. < 6, L > < 3,  > < 4, ; > < 6, Q2 > < 6, D > |
| 0 | < 6 , D > |. < 7,  > |
| 0 | < 6 , L > |. < 1, float > |
| 0 | < 6 , L > |. < 1, int > |
| 4 | < 6 , D > | < 6, L > < 3,  > < 4, ; > < 6, Q2 >. < 6, D > |

| Status:26 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 1 | < 6 , S > | < 6, S >. < 6, M > < 6, S > |
| 3 | < 6 , S > | < 6, S > < 6, M > < 6, S >. |

| Status:25 | Left | Right |
|---|---|---|
| 1 | < 6 , E > | < 6, E >. < 4, + > < 6, T > |
| 1 | < 6 , E > | < 6, E >. < 4, - > < 6, T > |
| 3 | < 6 , S > | < 3,  > < 4, = > < 6, E >. < 4, ; > |

| Status:24 | Left | Right |
|---|---|---|
| 0 | < 6 , C > |. < 6, E > < 4, < > < 6, E > |
| 0 | < 6 , C > |. < 6, E > < 4, == > < 6, E > |
| 0 | < 6 , C > |. < 6, E > < 4, > > < 6, E > |
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 3 | < 6 , S > | < 1, while > < 6, M > < 4, ( >. < 6, C > < 4, ) > < 6, M > < 6, S > |

| Status:23 | Left | Right |
|---|---|---|
| 3 | < 6 , S > | < 1, if > < 4, ( > < 6, C >. < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |

| Status:22 | Left | Right |
|---|---|---|
| 1 | < 6 , T > | < 6, F >. |

| Status:21 | Left | Right |
|---|---|---|
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 1 | < 6 , F > | < 4, ( >. < 6, E > < 4, ) > |

| Status:20 | Left | Right |
|---|---|---|
| 1 | < 6 , F > | < 3,  >. |

| Status:19 | Left | Right |
|---|---|---|
| 1 | < 6 , F > | < 2,  >. |

| Status:18 | Left | Right |
|---|---|---|
| 1 | < 6 , E > | < 6, T >. |
| 1 | < 6 , T > | < 6, T >. < 4, * > < 6, F > |
| 1 | < 6 , T > | < 6, T >. < 4, / > < 6, F > |

| Status:17 | Left | Right |
|---|---|---|
| 1 | < 6 , C > | < 6, E >. < 4, < > < 6, E > |
| 1 | < 6 , C > | < 6, E >. < 4, == > < 6, E > |
| 1 | < 6 , C > | < 6, E >. < 4, > > < 6, E > |
| 1 | < 6 , E > | < 6, E >. < 4, + > < 6, T > |
| 1 | < 6 , E > | < 6, E >. < 4, - > < 6, T > |

| Status:16 | Left | Right |
|---|---|---|
| 0 | < 6 , C > |. < 6, E > < 4, < > < 6, E > |
| 0 | < 6 , C > |. < 6, E > < 4, == > < 6, E > |
| 0 | < 6 , C > |. < 6, E > < 4, > > < 6, E > |
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , S > | < 1, if > < 4, ( >. < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |

| Status:15 | Left | Right |
|---|---|---|
| 2 | < 6 , S > | < 1, while > < 6, M >. < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |

| Status:14 | Left | Right |
|---|---|---|
| 0 | < 6 , E > |. < 6, E > < 4, + > < 6, T > |
| 0 | < 6 , E > |. < 6, E > < 4, - > < 6, T > |
| 0 | < 6 , E > |. < 6, T > |
| 0 | < 6 , F > |. < 2,  > |
| 0 | < 6 , F > |. < 3,  > |
| 0 | < 6 , F > |. < 4, ( > < 6, E > < 4, ) > |
| 0 | < 6 , T > |. < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, * > < 6, F > |
| 0 | < 6 , T > |. < 6, T > < 4, / > < 6, F > |
| 2 | < 6 , S > | < 3,  > < 4, = >. < 6, E > < 4, ; > |

| Status:13 | Left | Right |
|---|---|---|
| 0 | < 6 , S > |. < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 3,  > < 4, = > < 6, E > < 4, ; > |
| 0 | < 6 , S > |. < 6, S > < 6, M > < 6, S > |
| 2 | < 6 , S > | < 6, S > < 6, M >. < 6, S > |

| Status:12 | Left | Right |
|---|---|---|
| 0 | < 6 , Q2 > |. < 7,  > |
| 3 | < 6 , D > | < 6, L > < 3,  > < 4, ; >. < 6, Q2 > < 6, D > |

| Status:11 | Left | Right |
|---|---|---|
| 2 | < 6 , D > | < 6, L > < 3,  >. < 4, ; > < 6, Q2 > < 6, D > |

| Status:10 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 1 | < 6 , S > | < 6, S >. < 6, M > < 6, S > |
| 3 | < 6 , P > | < 6, Q1 > < 6, D > < 6, S >. |

| Status:9 | Left | Right |
|---|---|---|
| 1 | < 6 , S > | < 3,  >. < 4, = > < 6, E > < 4, ; > |

| Status:8 | Left | Right |
|---|---|---|
| 0 | < 6 , M > |. < 7,  > |
| 1 | < 6 , S > | < 1, while >. < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |

| Status:7 | Left | Right |
|---|---|---|
| 1 | < 6 , S > | < 1, if >. < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |

| Status:6 | Left | Right |
|---|---|---|
| 0 | < 6 , S > |. < 1, if > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > < 6, N > < 1, else > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 1, while > < 6, M > < 4, ( > < 6, C > < 4, ) > < 6, M > < 6, S > |
| 0 | < 6 , S > |. < 3,  > < 4, = > < 6, E > < 4, ; > |
| 0 | < 6 , S > |. < 6, S > < 6, M > < 6, S > |
| 2 | < 6 , P > | < 6, Q1 > < 6, D >. < 6, S > |

| Status:5 | Left | Right |
|---|---|---|
| 1 | < 6 , L > | < 1, int >. |

| Status:4 | Left | Right |
|---|---|---|
| 1 | < 6 , L > | < 1, float >. |

| Status:3 | Left | Right |
|---|---|---|
| 1 | < 6 , D > | < 6, L >. < 3,  > < 4, ; > < 6, Q2 > < 6, D > |

| Status:2 | Left | Right |
|---|---|---|
| 1 | < 6 , P' > | < 6, P >. |

| Status:1 | Left | Right |
|---|---|---|
| 0 | < 6 , D > |. < 6, L > < 3,  > < 4, ; > < 6, Q2 > < 6, D > |
| 0 | < 6 , D > |. < 7,  > |
| 0 | < 6 , L > |. < 1, float > |
| 0 | < 6 , L > |. < 1, int > |
| 1 | < 6 , P > | < 6, Q1 >. < 6, D > < 6, S > |

| Status:0 | Left | Right |
|---|---|---|
| 0 | < 6 , P > |. < 6, Q1 > < 6, D > < 6, S > |
| 0 | < 6 , P' > |. < 6, P > |
| 0 | < 6 , Q1 > |. < 7,  > |

#### Transfer Table
<table>
<tr>
<th rowspan="2"> # </th>
<th colspan="19">ACTION</th>
<th colspan="12">GOTO</th>
</tr>
<tr>
<th>< 1 , else ></th>
<th>< 1 , float ></th>
<th>< 1 , if ></th>
<th>< 1 , int ></th>
<th>< 1 , while ></th>
<th>< 2 ,  ></th>
<th>< 3 ,  ></th>
<th>< 4 , ( ></th>
<th>< 4 , ) ></th>
<th>< 4 , * ></th>
<th>< 4 , + ></th>
<th>< 4 , - ></th>
<th>< 4 , / ></th>
<th>< 4 , ; ></th>
<th>< 4 , < ></th>
<th>< 4 , = ></th>
<th>< 4 , == ></th>
<th>< 4 , > ></th>
<th>< 5 , $ ></th>
<th>< 6 , C ></th>
<th>< 6 , D ></th>
<th>< 6 , E ></th>
<th>< 6 , F ></th>
<th>< 6 , L ></th>
<th>< 6 , M ></th>
<th>< 6 , N ></th>
<th>< 6 , P ></th>
<th>< 6 , Q1 ></th>
<th>< 6 , Q2 ></th>
<th>< 6 , S ></th>
<th>< 6 , T ></th>
</tr>
<tr>
<td>0</td>
<td> </td>
<td> r1 </td>
<td> r1 </td>
<td> r1 </td>
<td> r1 </td>
<td> </td>
<td> r1 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 2 </td>
<td> 1 </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>1</td>
<td> </td>
<td> s4 </td>
<td> r3 </td>
<td> s5 </td>
<td> r3 </td>
<td> </td>
<td> r3 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 6 </td>
<td> </td>
<td> </td>
<td> 3 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>2</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> acc </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>3</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s11 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>4</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r6 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>5</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r5 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>6</td>
<td> </td>
<td> </td>
<td> s7 </td>
<td> </td>
<td> s8 </td>
<td> </td>
<td> s9 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 10 </td>
<td> </td>
</tr>
<tr>
<td>7</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s16 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>8</td>
<td> </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 15 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>9</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s14 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>10</td>
<td> </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r0 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 13 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>11</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s12 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>12</td>
<td> </td>
<td> r4 </td>
<td> r4 </td>
<td> r4 </td>
<td> r4 </td>
<td> </td>
<td> r4 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 27 </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>13</td>
<td> </td>
<td> </td>
<td> s7 </td>
<td> </td>
<td> s8 </td>
<td> </td>
<td> s9 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 26 </td>
<td> </td>
</tr>
<tr>
<td>14</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 25 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>15</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s24 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>16</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 23 </td>
<td> </td>
<td> 17 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>17</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s29 </td>
<td> s30 </td>
<td> </td>
<td> </td>
<td> s37 </td>
<td> </td>
<td> s38 </td>
<td> s39 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>18</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r16 </td>
<td> s35 </td>
<td> r16 </td>
<td> r16 </td>
<td> s36 </td>
<td> r16 </td>
<td> r16 </td>
<td> </td>
<td> r16 </td>
<td> r16 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>19</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r22 </td>
<td> r22 </td>
<td> r22 </td>
<td> r22 </td>
<td> r22 </td>
<td> r22 </td>
<td> r22 </td>
<td> </td>
<td> r22 </td>
<td> r22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>20</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r21 </td>
<td> r21 </td>
<td> r21 </td>
<td> r21 </td>
<td> r21 </td>
<td> r21 </td>
<td> r21 </td>
<td> </td>
<td> r21 </td>
<td> r21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>21</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 34 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>22</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r17 </td>
<td> r17 </td>
<td> r17 </td>
<td> r17 </td>
<td> r17 </td>
<td> r17 </td>
<td> r17 </td>
<td> </td>
<td> r17 </td>
<td> r17 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>23</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s33 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>24</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 32 </td>
<td> </td>
<td> 17 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>25</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s29 </td>
<td> s30 </td>
<td> </td>
<td> s31 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>26</td>
<td> r10 </td>
<td> </td>
<td> r10 </td>
<td> </td>
<td> r10 </td>
<td> </td>
<td> r10 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r10 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 13 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>27</td>
<td> </td>
<td> s4 </td>
<td> r3 </td>
<td> s5 </td>
<td> r3 </td>
<td> </td>
<td> r3 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 28 </td>
<td> </td>
<td> </td>
<td> 3 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>28</td>
<td> </td>
<td> </td>
<td> r2 </td>
<td> </td>
<td> r2 </td>
<td> </td>
<td> r2 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>29</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 49 </td>
</tr>
<tr>
<td>30</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 48 </td>
</tr>
<tr>
<td>31</td>
<td> r7 </td>
<td> </td>
<td> r7 </td>
<td> </td>
<td> r7 </td>
<td> </td>
<td> r7 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r7 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>32</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s47 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>33</td>
<td> </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 46 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>34</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s45 </td>
<td> </td>
<td> s29 </td>
<td> s30 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>35</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 44 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>36</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 43 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>37</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 42 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>38</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 41 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>39</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> s19 </td>
<td> s20 </td>
<td> s21 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 40 </td>
<td> 22 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 18 </td>
</tr>
<tr>
<td>40</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r12 </td>
<td> </td>
<td> s29 </td>
<td> s30 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>41</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r13 </td>
<td> </td>
<td> s29 </td>
<td> s30 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>42</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r11 </td>
<td> </td>
<td> s29 </td>
<td> s30 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>43</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r19 </td>
<td> r19 </td>
<td> r19 </td>
<td> r19 </td>
<td> r19 </td>
<td> r19 </td>
<td> r19 </td>
<td> </td>
<td> r19 </td>
<td> r19 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>44</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r18 </td>
<td> r18 </td>
<td> r18 </td>
<td> r18 </td>
<td> r18 </td>
<td> r18 </td>
<td> r18 </td>
<td> </td>
<td> r18 </td>
<td> r18 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>45</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r20 </td>
<td> r20 </td>
<td> r20 </td>
<td> r20 </td>
<td> r20 </td>
<td> r20 </td>
<td> r20 </td>
<td> </td>
<td> r20 </td>
<td> r20 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>46</td>
<td> </td>
<td> </td>
<td> s7 </td>
<td> </td>
<td> s8 </td>
<td> </td>
<td> s9 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 51 </td>
<td> </td>
</tr>
<tr>
<td>47</td>
<td> </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 50 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>48</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r15 </td>
<td> s35 </td>
<td> r15 </td>
<td> r15 </td>
<td> s36 </td>
<td> r15 </td>
<td> r15 </td>
<td> </td>
<td> r15 </td>
<td> r15 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>49</td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r14 </td>
<td> s35 </td>
<td> r14 </td>
<td> r14 </td>
<td> s36 </td>
<td> r14 </td>
<td> r14 </td>
<td> </td>
<td> r14 </td>
<td> r14 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>50</td>
<td> </td>
<td> </td>
<td> s7 </td>
<td> </td>
<td> s8 </td>
<td> </td>
<td> s9 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 53 </td>
<td> </td>
</tr>
<tr>
<td>51</td>
<td> r24 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 13 </td>
<td> 52 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>52</td>
<td> s54 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>53</td>
<td> r9 </td>
<td> </td>
<td> r9 </td>
<td> </td>
<td> r9 </td>
<td> </td>
<td> r9 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r9 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 13 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>54</td>
<td> </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> </td>
<td> r23 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 55 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
<tr>
<td>55</td>
<td> </td>
<td> </td>
<td> s7 </td>
<td> </td>
<td> s8 </td>
<td> </td>
<td> s9 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 56 </td>
<td> </td>
</tr>
<tr>
<td>56</td>
<td> r8 </td>
<td> </td>
<td> r8 </td>
<td> </td>
<td> r8 </td>
<td> </td>
<td> r8 </td>
<td> r23 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> r8 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> 13 </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>
</table>
### Intermediate Code Generation
```
0: a = 2
1: b = 1
2: if a > b goto 4
3: goto 7
4: t = a + b
5: c = t
6: goto 
7: t = a - b
8: c = t
```
