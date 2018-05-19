# Towards automatic argumentation about voting rules

Towards automatic voting rule argumentation by using computer-aided verification such as software bounded model checking.

More details are explained in the corresponding [paper](https://formal.iti.kit.edu/biblio/?lang=en&key=KirstenCailloux2018).

The entry point should be the script [``arguing.sh``](arguing.sh), where (axiomatic) properties can be chosen via the file [``properties.in``](properties.in)
and voting rules via [``rules.h``](rules.h).

Furthermore, you must specify the bounds for the number of alternatives and the number of voters.
Assuming you choose the numbers **_m_** for alternatives and **_n_** for voters, you would type the following in your shell:

```
./arguing.sh m n
```

For a quick access of the voting rules and axioms from the paper, we provided some preconfigured scripts and property files
to be called using the scripts [``borda.sh``](borda.sh), [``black.sh``](black.sh) and [``copeland.sh``](copeland.sh) (which call the respective voting rules)
together with the desired property file as the first argument (with the bounds for alternatives and voters as second and third argument, respectively).
The property files used in the paper are [``canc.in``](canc.in), [``cond.in``](cond.in), [``cycl.in``](cycl.in), [``dom.in``](dom.in),
[``domNeg.in``](domNeg.in), [``elem.in``](elem.in), [``majo.in``](majo.in), [``reinf.in``](reinf.in) and [``wmaj.in``](wmaj.in) which are used to verify
(or produce a counter-example for) the respective properties cancellation, Condorcet, cyclicity, Pareto dominance, negated Pareto dominance,
elementary profile, majority, reinforcement, and weak majority.


For more information, please contact [Michael Kirsten](https://formal.iti.kit.edu/~kirsten/?lang=en)
or [Olivier Cailloux](https://www.lamsade.dauphine.fr/~ocailloux/).
