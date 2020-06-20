# vemacs text Editor


## TODO:
- buf testing
- Window Management
- State cleanup in closing

## Buffer testing classes
1            2       3
|------------|-------|
sl, tl, ll, el
#### 1.
```c
if (tl < ll) { // sl - »tl - ll - el
    // ot_size diff = (ll - sl) / 2;
    return tl < (ll / 2) ? sl : ll;
    if (tl < (ll / 2)) {
        return sl; // dir forwards
    } else {
        return ll; // dir backwards
    }

} else { // sl - ll - »tl - el
    // ot_size diff = (el - ll) / 2;
    if (tl < (ll + ((el - ll) / 2))) {
        return ll; // dir forwards
    } else {
        return el; // dir backwards
    }
}


```
#### 2.

#### 3.

