# MINISHELL
---

echo $  
'e'c'h'o'' $  
"echo hello"  
echo '$ENV'  
echo "$ENV$?"  

```
<f1<f2<f3 cat >f4>f5>f6 read form f3 put to f6 but create f4 f5
```


lexical analyzer


loop throght lexel list 

first word found treate if as cmd
if found redir out open it and dup it to stdout
if found redir in open it and read all file then keep it untill find it was read



## lexical analysis

error case 
> echo 1 2 3 4 5 6 8 9  
> reallocate char **argv  

### bash refference
#### redirect out

```
f3 not exist, f2 exist  
> >f3 echo hell  
# echo "hell" to f3  
> >f1>f2>f3  
# open or create when file not exist
```

#### redirect in  

f3 not exist, f2 exist  
> echo < f3 f2  
- if no file f3 whole command token will return error  
> echo < f3 f2 | ls  
- $? = 0 , ls work  
> ls | echo < f3 f2  
- $? = 1 promt show error -> f3: No such file or directory 


#### in & out  
```
f3 not exist, f2 exst
> <f3 >f3 echo hello
- error, f3 no file
> >f3 <f3 echo hello
- create f3 and echo hello into it
```


Note create strcmp  --> do unit test
set path to env
