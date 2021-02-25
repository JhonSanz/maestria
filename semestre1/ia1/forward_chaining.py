
class Solver:
    a = "Tos seca"
    b = "Fiebre"
    c = "Malestar"
    HYPOTESIS = "Covid 19"
    """ Base de hechos, hechos inciales, BH """
    INITIAL_FACTS = {a,b,c} 
    """ Base de conocimiento, BC """
    KNOWLEDGE_BASE = {}

    def heuristic(self, conflict_set):
        """
            - Choose a rule by any way
        """
        rule = list(conflict_set)[0]
        return rule

    def resolve(self, conflict_set):
        """ Resolve conflict set
            - Choose a rule using heristic
            - Get rule result
            - return rule result and rule
        """
        rule = self.heuristic(conflict_set)
        return rule.get_result(), rule

    def generate_conflict_set(b_c, self, b_h):
        """ Conflict set
            All rules that have as antecedents one or more of
            initial facts

            - Search rules that have as antecedets initals facts
            - Put that rules into conflict set
        """
        pass

    def forward_chaining(self):
        visited = set()
        while(
            not self.HYPOTESIS in self.KNOWLEDGE_BASE
            and conflict_set
        ):
            """ Updates conflict set excluding visited rules """
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

solver = Solver()
solver.forward_chaining()
