
class Rule:
    __facts = set()
    __result = ""
    __certainty_factor = 0

    def __init__(self, facts, result, certainy_factor):
        self.__facts = self.__facts.add(*facts)
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

    def heuristic(self, conflict_set):
        rule = list(sorted(conflict_set))[0]
        return rule

    def resolve(self, conflict_set):
        rule = self.heuristic(conflict_set)
        return rule.result, rule

    def generate_conflict_set(b_c, self, b_h):
        pass

    def accumulate_evidence(self):
        pass

    def forward_chaining(self):
        visited = set()
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
                ).difference_update(visited)
            )
            if conflict_set:
                fact, rule = self.resolve(conflict_set)
                self.INITIAL_FACTS.add(fact)
                visited.add(rule)
                self.accumulate_evidence()


solver = Solver()
solver.forward_chaining()
