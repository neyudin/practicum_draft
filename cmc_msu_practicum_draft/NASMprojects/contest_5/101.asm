%include "io.inc"

		        	SECTION .data
			            A DD F1, F2, 0, F3, 0, F4

        			SECTION .text

                    GLOBAL CMAIN
                    CMAIN:
		        	    PUSH	        EBP
        			    GET_DEC	        4, EAX
		        	    GET_CHAR	    CL
        			    GET_DEC	        4, EBX
		        	    SUB     	    CL, 42
			            MOVZX   	    EBP, CL
        			    LEA     	    EBP, [A + 4 * EBP]
		        	    CALL    	    [EBP]
			            PRINT_DEC       4, EAX
        			    NEWLINE
		        	    POP		        EBP
			            XOR     	    EAX, EAX
        			    RET

		        	F1:
			            IMUL    	    EAX, EBX
        			    RET

		        	F2:
			            ADD     	    EAX, EBX
        			    RET

		        	F3:
			            SUB     	    EAX, EBX
        			    RET

		        	F4:
			            CDQ
        			    IDIV    	    EBX
		        	    RET