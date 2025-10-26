# Contributing
## Coding style

### File structure
Every krabascript's source code must included this header:

```
/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Do stuff
  Copyright:    Copyright 2025 John Doe <ilovekrabas@example.com>
*/
```

You can add yourself to the Copyright list if you're responsible for the whole file or a part of it. Max 5 people can be inside the list.

### Indentation

1. A line must be max 90 columns wide
2. Use 4 spaces instead of tabs
3. Don't use spaces around unary operators

**Right:**
```i++;```

**Wrong:**
```i++ ;```

4. Put spaces around operators

**Right:**
```x << 5```

**Wrong:**
```x<<5```

5. Don't place spaces between a comma and a semicolon
6. Capitalize names of variables and functions.