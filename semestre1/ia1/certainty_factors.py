from copy import deepcopy

class Rule:
    __facts = set()
    __result = ""
    __certainty_factor: float = 0

    def __init__(self, facts, result, certainy_factor):
        self.__facts = self.__facts.update(facts)
        self.__result = result
        self.__certainty_factor = certainy_factor

    @property
    def certainty_factor(self):
        return self.__certainty_factor

    @property
    def result(self):
        return self.__result

    @property
    def facts(self):
        return self.__facts

    def __eq__(self, other):
        return (
            self.__facts == other.facts and
            self.__result == other.result and
            self.__certainty_factor == other.certainty_factor
        )

    def __ne__(self, other):
        return not(self == other)

    def __gt__(self, other):
        return self.__certainty_factor > other.certainty_factor

    def __ge__(self, other):
        return self.__certainty_factor >= other.certainty_factor

    def __lt__(self, other):
        return self.__certainty_factor < other.certainty_factor

    def __le__(self, other):
        return self.__certainty_factor <= other.certainty_factor


class Solver:
    a = "Tos seca"
    b = "Fiebre"
    c = "Malestar"
    HYPOTESIS = "Covid 19"
    INITIAL_FACTS = {a,b,c} 
    KNOWLEDGE_BASE: Rule = set()
    evidence = 0

    def zadeh(self):
        """ If rule has multiple premises then for any record
            - if are connected with & -> choose min 
            - if are connected with | -> choose max
        """
        pass

    def heuristic(self, conflict_set):
        rule = list(sorted(
            conflict_set,
            key=lambda rule: rule.certainty_factor
        ))[0]
        return rule

    def resolve(self, conflict_set):
        rule = self.heuristic(conflict_set)
        return rule.result, rule

    def generate_conflict_set(self, b_c, b_h, visited=set()):
        __b_c = deepcopy(b_c).difference_update(visited)
        conflict_set = set()
        for fact in b_h:
            for rule in __b_c:
                if fact in rule.facts:
                    conflict_set.add(rule)
        return conflict_set

    def __relative_sum(self, rule_factor):
        return (
            rule_factor * (1 - self.evidence)
            if self.evidence != 0
            else rule_factor
        )

    def accumulate_evidence(self, rule):
        self.evidence += self.__relative_sum(rule.certainty_factor)

    def forward_chaining(self):
        visited: Rule = set()
        conflict_set = (
            self.generate_conflict_set(
                self.KNOWLEDGE_BASE,
                self.INITIAL_FACTS
            )
        )
        while(
            not self.HYPOTESIS in self.KNOWLEDGE_BASE
            and conflict_set
        ):
            conflict_set = (
                self.generate_conflict_set(
                    self.KNOWLEDGE_BASE,
                    self.INITIAL_FACTS
                )
            )
            if conflict_set:
                fact, rule = self.resolve(conflict_set)
                self.INITIAL_FACTS.add(fact)
                visited.add(rule)
                self.accumulate_evidence()


solver = Solver()
solver.forward_chaining()
