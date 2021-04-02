# Note about C++ Language 

## Why C++
- Fully Controlled & High Performance; 
    - Able to control the memory allocation, no need gc;
    - Able to control whether copy or move memory buffer;
- Having utilities to protected the ownership of resources;
- Having utilities/pattern to protected the memory problem (vs C lang);
    
## Data Ownership 
```
class Main : Noncopyable {
    Factory factory;
    Vector<std:shared_ptr<Item>> itemPool;
}
class Factory : Noncopyable  {
    std::unique_ptr<Item> create();
}
class Item: Noncopyable {    
}
```
- Using Reference: A data owned by a master resource. E.g `Main.factory` 
- Using unique_ptr: The creator won't own the resource or the user will own it. E.g `Factory.create`
- Using shared_ptr: The owner instance allow to share the access to others.

## Consts 

## Type cast 