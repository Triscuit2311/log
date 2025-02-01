### Log
This library is the result of years of incremental changes and indescision. I have used some iteration of this for countless projects, almost never leaving it alone. I finally decided to unify everything into one consistent header-only library. This is by and far not the best way to log, nor the fastest, but it's convienent and I like it.

---
### Usage

```cpp
logger::con.init(); //call once


//Log levels
//all take any w/string or w/c string
logger::con.log("Hello");
logger::con.info(std::string("Bonjour"));
logger::con.special(L"哈囉");
logger::con.err(std::wstring(L"Ciao!"));

// printf-style var args
// Also any combination of strings and wide strings is fine in fmt and var args!
logger::con.log(L"Hi, My name is %s and I'm %d years old.", std::string("Dante"), 32);


logger::con.free(); // free console any time! Detaches, doesnt close.
```
