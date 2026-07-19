# quantity-engine

Quantity is not just an engine but a framework of modules that allow you to quickly make software just by plugging them into an `Application`. I chose to design it like this due to previous engine editor relationships, the biggest issue I had was that my editor had to really hack through the engine to turn off specific parts of its runtime. This also has the benefit of faster build times thanks to ninja, so you only rebuild modules and their dependents when source code is changed.

Yes, it is quite inspired by Source Engine. :)

# Why so sparse?
This used to be a more complete engine featuring entity components and some simple rendering tech, but now I am doing a major rewrite for modularization so I can encourage reusabilty and ease app relations.

# How do I make applications with this?
TODO reference basicapp