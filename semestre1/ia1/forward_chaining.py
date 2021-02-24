

def resolve(conflict_set):
    """ Resolve conflict set
        - Choose a rule using heristic
        - Get rule returning
        - Put into conflict_set
    """
    pass

def initialize_conflict_set(b_c, b_h):
    pass

def forward_chaining(b_c, b_h, h):
    conflict_set = initialize_conflict_set(b_c, b_h)
    while(
        not h in k_b and
        conflict_set and
    ):
        conflict_set = 
        if conflict_set:
            resolve(conflict_set)
            new_facts = 


a = "Tos seca"
b = "Fiebre"
c = "Malestar"
h = "Covid 19"
INITIAL_FACTS = {a,b,c} # Base de hechos
KNOWLEDGE_BASE = {}

forward_chaining(INITIAL_FACTS, KNOWLEDGE_BASE, h)
