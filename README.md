# 42cursus-minishell
The objective of this project is for you to create a simple shell. Yes, your<br/>
little bash or zsh. You will learn a lot about processes and file descriptors<br/>

## Introduction:
The existence of shells is linked to the very existence of IT. At the time, all coders agreed<br/>
that communicating with a computer using aligned 1/0 switches was seriously<br/>
irritating. It was only logical that they came up with the idea to communicate with<br/>
a computer using interactive lines of commands in a language somewhat close to english.<br/>
With Minishell, you’ll be able to travel through time and come back to problems<br/>
people faced when Windows didn’t exist.<br/>

Your shell should:
---
• Not interpret unclosed quotes or unspecified special characters like \ or ;.<br/>
• Not use more than one global variable, think about it and be ready to explain why you do it.<br/>
• Show a prompt when waiting for a new command.<br/>
• Have a working History.<br/>
• Search and launch the right executable (based on the PATH variable or by using relative or absolute path)<br/>
• It must implement the builtins:<br/>
>>◦ echo with option -n<br/>
>>◦ cd with only a relative or absolute path<br/>
>>◦ pwd with no options<br/>
>>◦ export with no options<br/>
>>◦ unset with no options<br/>
>>◦ env with no options or arguments<br/>
>>◦ exit with no options<br/>
>• ’ inhibit all interpretation of a sequence of characters.<br/>
>• " inhibit all interpretation of a sequence of characters except for $.<br/>
>• Redirections:<br/>
>>◦ < should redirect input.<br/>
>>◦ > should redirect output.<br/>
>>◦ “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!<br/>
>>◦ “>>” should redirect output with append mode.<br/>
>• Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.<br/>
>• Environment variables ($ followed by characters) should expand to their values.<br/>
>• $? should expand to the exit status of the most recently executed foreground pipeline.<br/>
>• ctrl-C ctrl-D ctrl-\ should work like in bash.<br/>
>• When interactive:<br/>
>>◦ ctrl-C print a new prompt on a newline.<br/>
>>◦ ctrl-D exit the shell.<br/>
>>◦ ctrl-\ do nothing.<br/>
readline function can produce some leak you don’t need to fix this.<br/>
But beware your own code should not produce leaks.<br/>
You should limit yourself to the subject description.<br/>
Anything not asked is not required.<br/>
For every point, if you have any doubt take bash as a reference.<br/>
