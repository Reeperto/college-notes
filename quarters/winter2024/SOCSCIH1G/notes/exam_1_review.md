# Questions

**1. What are social facts and social phenomena**

Durkheim's definition is 

>   "A social fact is any way of acting, whether fixed or not, capable of exerting over the individual an external constraint;
>   or:
>   which is general over the whole of a given society whilst having an existence of its own, independent of its individual manifestations"

**2. Descriptive versus Normative Description**

A descriptive account tries to capture what the idea or thing is, while normative is a prescription of how things should be.

For example,

| **Descriptive** | **Normative** |
|---|---|
|I go to sleep at 10 PM each night|People should sleep at 9 PM every day|

**3. Why are Law's not just universal conditions / generalities**

By counterexample, the pear basket shows how a simple universal condition does not capture. For clarification, universal in universal condition is a synonym for general.

**4. Clarifying the functional/teleological model of explanation**

Functional explanation is built around establishing an explanation for why something exists. The argument made is one appealing to the function/purpose something serves to reach the conclusion. Usually, when you have some variable X explaining Y functionally, X is the purpose of Y. 

```{.graphviz caption="The functional explanation for why lungs exist in mammals"}
digraph functional {
    graph [fontsize=10 fontname="PragmataPro" compound=true];
	rankdir=LR;
	node [shape = plaintext, fontname="PragmataPro"]; 

    subgraph cluster_explanans {
        X [label = "Survival is a goal of mammals"];
        graph[style = "dotted", label = "Explanans"]
    }

    subgraph cluster_explanandum {
        Y [label = "Lungs provide oxygen"]; 
        Z [label = "Oxygen is essential for survival"];
        Y -> Z;
        graph[style = "dotted", label = "Explanadum"]
    }

    X -> Y [ltail = cluster_explanans, lhead = cluster_explanandum, minlen = 2];
}
```

Functional explanation is different than other explanation in terms of time. In a casual explanation, the effects follow in time from their causes. In the lung example, the purpose or function of the lungs follows their existence in time, yet the purpose is the explanans or X.

**4. What is multiple realizations?**

Multiple realizations is capturing the idea of abstraction. Money is an example of an abstract concept as their are multiple physical/concrete things we call money such as dollar bills, metal coins, digital currency, etc. Even though these are all different "low" level physical things, they still all are understood through a general term "Money".

# Things to Know

- Know the counterexamples and examples associated with each model and their potential problems
    - Know what the deeper problem is that they highlight
