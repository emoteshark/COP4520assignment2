# COP4520assignment2

#Part 1: Minotaur Birthday (part1.cpp)
Strategy:
The first guest will find a cupcake at the end 100% of the time, and should eat it. Assuming
this guest can see the cupcake after leaving the labryinth (which is not specified but I dont
see how it's solvable otherwise), the first guest should wait and count every time the plate is left
empty after a guest leaves, because each guest should only eat a cupcake (leaving the plate empty) on
their first time in the labryinth. If they enter again they should leave the cupcake on the plate. This
way every time a guest passes through and the plate is empty the counter will know that that guest is going
through for the first time.

The number of guests is a #define, so the number of guests at the party can easily be changed.

#Part 2: Minotaur Vase (part2.cpp)

I think the third strategy (the queue) is the best in terms of maximizing the amount of people who can see the vase. The first strategy is chaotic and many guests will waste time checking the door. The second strategy is better, but assuming guests are wandering around the party, there may be times where there are no guests in the vase room if nobody is checking the sign. The queue does not allow the guests to enjoy the party while they wait in line, but it is the most orderly and efficient way to make sure there is always a guest in the vase room and nobody is confused about whether they may enter or not.
