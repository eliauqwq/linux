# 文件与目录命令——grep
grep命令是一个十分便捷的文本过滤工具，来源于" *global regular expression print* "。它可以帮助我们十分便捷地在文件或者输出流中查找匹配某些特定模式（*pattern*）的目标及其个数、位置等。

## grep语法的基础结构
```
grep [匹配选项] "匹配模式" [待匹配目标]
```

很容易理解，匹配选项就是我们需要如何匹配（动词）模式，而匹配模式则是我们需要匹配的文本，待匹配目标就是亟待解决的目标。

## grep的常见选项及其用法案例

1. `-i`,忽略模式的大小写，对应`ignore-case`。例如我们现在需要在bat文件中寻找包含hello这个模式的行，不考虑大小写：
```
grep -i "hello" bat
```
2. `-v`,取反匹配到模式的行，也就是将不匹配模式的行列出来，对应`invert-match`,也就是反转匹配。找到bat不匹配hello的行：
```
grep -v "hello" bat
```
3. `-c`,只返回匹配到模式的行的总数目，对应`count`。例如找到bat中匹配aaa的行的行数：
```
grep -c "aaa" bat
```
4. `-n`,要求一同返回匹配成功行的行号，对应`number`。
找到bat中匹配failure的行及其行号：
```
grep -n "failure" bat
```

5. `-l`，要求返回包含匹配模式的行的文件，常常与通配符一同使用,对应`list`——*列表*。例如，在后缀是.log的文件中找到有error的行的文件：
```
grep -l "error" *.log
```

6. `-w`,要求模式按整个单词来匹配，不考虑模式不为完整单词的行数，对应`word`。例如在bat中查找含有单词hello的行：
```
grep -w "hello" bat
```

7. `-r`,要求在给定目录下查找存在模式的行及其所在文件。对应`recursive`——*递归*。例如在/path/to路径下查找匹配error的行及其文件：
```
grep -r "error" /path/to
```
8. `-o`,仅仅返回匹配的模式，不返回整行，常常与`-n`一起配合查找关键词，对应`only`仅匹配模式。例如，在bat中查找是否存在关键词faliure及其位置：
```
grep -on "failure" bat
```

9. `-A n`,返回匹配成功的行及其后n行的信息，对应`after`。例如在bat中查找存在关键词error及其后面两行信息：
```
grep -A n "error" bat
```

10. `-B n`,和`-A n`类似，只不过这个返回的是匹配成功行的前n行

11. `-C n`,返回前后各n行,对应`context`——*上下文*。

12. `-e`,匹配多个模板中的任意一个的行，对应`either`,
例如在bat中查找匹配error或者failure的行
```
grep -e "error" -e "failure" bat
```

## 正则表达式在grep中的应用
1. `.`,表示匹配的任意单个字符,例如
```
grep -n "h.o" bat
```
表示在bat中的任何带有b t的行，可能有bet,brt。

2. `^`,表示以给定字符串开头的行，例如在bat中找到任何以error开头的行
```
grep -n "^error" bat
```
3. `$`,表示给定字符结尾，例如在bat中找到任何以error结尾的行:
```
grep -n "error$" bat
```
4. `[]`，表示一个字符集中的任意字母，例如找到包含字母a、e的行:
```
grep -n "[a,e]" bat
```
5.`*`,表示匹配前一个字符**一次个或者多此**，例如在bat中找到a   的行
```
grep -n "a*" bat
```
