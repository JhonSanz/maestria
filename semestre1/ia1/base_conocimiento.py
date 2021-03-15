exp_years: int = 4 # Años de experiencia
exp_open: int = 2 # Producto abierto en los últimos 6 meses 
exp_prods: int = 6 # Cantidad de productos positivos
exp_last_open: int = 2 # Tiempo desde última apertura (meses)
debt_usage: float = 0.38 # Porcentaje de utilización en la capacidad de endeudamiento (< 55%)
debt_fixed_loan: bool = False # Préstamos a plazo fijo, créditos de libre inversión
debt_stable: bool = False # Comportamiento estable (variabilidad en el endeudamiento, a mayor estabilidad menor riesgo)
stat_open: int = 0 # Cantidad de productos abiertos
stat_mortgage: bool = True # Crédito hipotecario/leasing 
stat_financial_com: int = 2 # Cuenta con productos financieros y telecomunicaciones
stat_codebtor: bool = True # No tienes cuentas como codeudor
habit_debt_30: bool = True # Productos con moras de 30 días
habit_debt_60: bool = False # Productos con moras de 60 días
habit_debt_balance: bool = False # Saldo en mora actual
habit_debt_prods: int = 1 # Cantidad productos en mora


DEFINITIONS

    EXPERIENCE = {
        "exp_years": 1 if exp_years > 5 else 0,
        "exp_open": 1 if exp_years in [0, 1] else 0,
        "exp_prods": 1 if exp_prods > 5 else 0,
        "exp_last_open": 1 if exp_last_open > 3 else 0,
    }
    DEBT = {
        "debt_usage": 1 if debt_usage < 55 else 0,
        "debt_fixed_loan": bool,
        "debt_stable": bool,
    }
    PORTFOLIO_STATUS = {
        "stat_open": 1 if stat_open > 4 else 0,
        "stat_mortgage": bool,
        "stat_financial_com": 1 if stat_financial_com > 1 else 0,
        "stat_codebtor": bool,
    }
    PAYMENT_BEHAVIOUR = {
        "habit_debt_30": bool,
        "habit_debt_60": bool,
        "habit_debt_balance": bool,
        "habit_debt_prods": 1 if habit_debt_prods > 1 else,
    }


RULES

    # R1
    EXPERIENCE = (
        {
            "exp_years": 0.7,
            "exp_open": 0.4,
            "exp_prods": 0.6,
            "exp_last_open": 0.2,
        },
        {
            ln: 
            ls: 
        },
        
    )

    # R2
    DEBT = (
        {
            "debt_usage": 0.8,
            "debt_fixed_loan": 0.5,
            "debt_stable": 0.7,
        },
        {
            ln: 
            ls: 
        }
    )

    # R3
    PORTFOLIO_STATUS = (
        {
            "stat_open": 0.4,
            "stat_mortgage": 0.2,
            "stat_financial_com": 0.3,
            "stat_codebtor": 0.7,
        },
        {
            ln: 
            ls: 
        }
    )

    # R4
    PAYMENT_BEHAVIOUR = (
        {
            "habit_debt_30": 0.3,
            "habit_debt_60": 0.6,
            "habit_debt_balance": 0.8,
            "habit_debt_prods": 0.9,
        },
        {
            ln: 
            ls: 
        }
    )