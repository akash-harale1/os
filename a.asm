START 101
READ N
MOVER BREG ONE
MOVER BREG ONE
MOVER BREG ONE
MOVEM BREG =5
AGAIN MULT BREG TERM
MOVER CREG TERM
ADD CREG ONE
LTORG
MOVEM CREG =6
COMP CREG N
BC LE AGAIN
DIV BREG TWO
MOVEM BREG RESULT
PRINT RESULT
STOP

N DS 1
RESULT DS 1
ONE DS '1'
TERM DS 1
TWO DC '2'
END
