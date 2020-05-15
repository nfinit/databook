
1 REM * COMPUTER BRIDGE *
2 REM * JUNE 1989 ISSUE *
3 ! S/J=L, F/L=R, D/K=TURN, SPACE=DROP, Q=END, P=PAUSE
100 DISPLAY ERASE ALL AT(8,12):"TETRIS" :: DISPLAY AT(10,3):"(C) 1989 STEVEN KARASEK"
110 PRINT "STARTING LEVEL (1-9)";:: INPUT E :: E=INT(E):: IF E<1 OR E>9 THEN 110 ELSE E=10-E
120 DIM Z$(23),Z(26),A(18,3),B(18,3):: RANDOMIZE :: C$="JKL; UQSDFARP" :: Z(24)=4095 :: CALL MAGNIFY(4):: CALL CLEAR :: FOR I=0 TO 6
130 READ N(I),C(I):: CALL COLOR(I+8,2,C(I)):: NEXT I :: FOR I=0 TO 18 :: FOR J=0 TO 3 :: READ A(I,J),B(I,J):: NEXT J :: NEXT I
140 FOR I=68 TO 143 :: READ X$ :: CALL CHAR(I,X$):: NEXT I :: CALL CHAR(41,"FFFFFFFFFFFFFFFF")
150 FOR I=0 TO 23 :: Z$(I)=RPT$(")",10):: Z(I)=2049 :: NEXT I :: V=E :: D,P=24 :: U=0 :: GOSUB 450 :: CALL VCHAR(1,12,41,240)
160 CALL KEY(0,M,W):: IF W<>1 THEN 160
170 P=0 :: Q=4 :: J=INT(RND*7):: S=J*2 :: J8=J*8+89 :: IF J>3 THEN S=S-1+2*(J-4)
180 GOSUB 470 :: T=0 :: X=1 :: Y=Q*8+81 :: CALL SPRITE(#1,K,C(J),X,Y)
190 IF Z(0)AND 2^(Q+Y1)OR Z(X2)AND 2^(Q+Y2)OR Z(X3)AND 2^(Q+Y3)OR Z(X4)AND 2^(Q+Y4)THEN 430
200 FOR I=1 TO V :: CALL KEY(0,M,W):: IF M<0 THEN 350 ELSE ON POS(C$,CHR$(M),1)+1 GOTO 350,210,280,230,340,250,330,440,210,280,230,340,330,600
210 Q=Q-1 :: IF Z(P)AND 2^(Q+Y1)OR Z(P+X2)AND 2^(Q+Y2)OR Z(P+X3)AND 2^(Q+Y3)OR Z(P+X4)AND 2^(Q+Y4)THEN Q=Q+1 ELSE Y=Y-8
220 CALL LOCATE(#1,X,Y):: GOTO 350
230 Q=Q+1 :: IF Z(P)AND 2^(Q+Y1)OR Z(P+X2)AND 2^(Q+Y2)OR Z(P+X3)AND 2^(Q+Y3)OR Z(P+X4)AND 2^(Q+Y4)THEN Q=Q-1 ELSE Y=Y+8
240 GOTO 220
250 Y1=2^(Q+Y1):: Y2=2^(Q+Y2):: Y3=2^(Q+Y3):: Y4=2^(Q+Y4):: GOSUB 450 :: P=MAX(P,D-X4)
260 IF (Z(P)AND Y1 OR Z(P+X2)AND Y2 OR Z(P+X3)AND Y3 OR Z(P+X4)AND Y4)=0 THEN P=P+1 :: GOTO 260
270 P=P-1 :: CALL LOCATE(#1,P*8+1,Y):: CALL SOUND(10,440,0):: GOTO 380
280 S=S-1 :: T=T-1 :: IF T<0 THEN T=N(J)-1 :: S=S+N(J)
290 GOSUB 470
300 IF (Z(P)AND 2^(Q+Y1)OR Z(P+X2)AND 2^(Q+Y2)OR Z(P+X3)AND 2^(Q+Y3)OR Z(P+X4)AND 2^(Q+Y4))=0 THEN CALL PATTERN(#1,K):: GOTO 350
310 S=S+1 :: T=T+1 :: IF T=N(J)THEN T=0 :: S=S-N(J)
320 GOSUB 470 :: GOTO 350
330 CALL KEY(0,M,W):: IF W<>0 THEN 330 ELSE V=V+(V>1):: GOSUB 460 :: GOTO 350
340 CALL KEY(0,M,W):: IF W<>1 THEN 340
350 NEXT I :: P=P+1 :: IF P+X4>=D THEN 370
360 X=X+8 :: CALL LOCATE(#1,X,Y):: GOTO 200
370 IF (Z(P)AND 2^(Q+Y1)OR Z(P+X2)AND 2^(Q+Y2)OR Z(P+X3)AND 2^(Q+Y3)OR Z(P+X4)AND 2^(Q+Y4))=0 THEN 360 ELSE P=P-1 :: GOSUB 450
380 D=MIN(D,P):: FOR I=0 TO 3 :: W=Q+B(S,I):: M=P+A(S,I):: Z(M)=Z(M)+2^W :: Z$(M)=SEG$(Z$(M),1,W-1)&CHR$(J8)&SEG$(Z$(M),W+1,10)
390 CALL HCHAR(M+1,W+11,J8):: NEXT I :: CALL DELSPRITE(#1):: FOR I=MIN(P+3,23)TO P STEP -1 :: IF Z(I)<4095 THEN 420 ELSE J=I :: M=I-1
400 Z(J)=Z(M):: Z$(J)=Z$(M):: DISPLAY AT(J+1,10):Z$(J):: IF Z(J)>2049 THEN J=J-1 :: M=M-1 :: GOTO 400
410 U=U+INT(500/V):: GOSUB 460 :: I=I+1 :: P=P-1 :: D=D+1
420 NEXT I :: GOTO 170
430 H=MAX(H,U):: DISPLAY AT(1,20):USING "#########":H :: CALL DELSPRITE(#1):: GOTO 150
440 DISPLAY ERASE ALL:"HIGH SCORE IS";MAX(U,H):: END
450 U=U+INT((24-P)*100/V)
460 DISPLAY AT(3,20):USING "#########":U :: V=MIN(V,MAX(1,9-INT(U/5000))):: DISPLAY AT(3,4)SIZE(2):10-V :: RETURN
470 X2=A(S,1):: X3=A(S,2):: X4=A(S,3):: Y1=B(S,0):: Y2=B(S,1):: Y3=B(S,2):: Y4=B(S,3):: K=68+S*4 :: RETURN
480 DATA 2,15,2,7,2,14,1,16,4,11,4,4,4,5
490 DATA 0,0,0,1,0,2,0,3,0,1,1,1,2,1,3,1,0,0,0,1,1,1,1,2,0,2,1,1,1,2,2,1
500 DATA 0,1,0,2,1,0,1,1,0,1,1,1,1,2,2,2,0,1,0,2,1,1,1,2,0,1,1,0,1,1,1,2
510 DATA 0,1,1,1,1,2,2,1,0,0,0,1,0,2,1,1,0,2,1,1,1,2,2,2
520 DATA 0,0,1,0,1,1,1,2,0,1,0,2,1,1,2,1,0,0,0,1,0,2,1,2,0,2,1,2,2,1,2,2
530 DATA 0,2,1,0,1,1,1,2,0,1,1,1,2,1,2,2,0,0,0,1,0,2,1,0,0,1,0,2,1,2,2,2
540 DATA FFFFFFFF,,FFFFFFFF,,0F0F0F0F0F0F0F0F,0F0F0F0F0F0F0F0F,,
550 DATA FFFFFFFF0F0F0F0F,,00000000F0F0F0F,,000000000F0F0F0F,0F0F0F0F,F0F0F0F0F0F0F0F0,,0F0F0F0FFFFFFFFF,,F0F0F0F,
560 DATA 0F0F0F0F0F0F0F0F,,00000000F0F0F0F0,F0F0F0F,0F0F0F0F0F0F0F0F,,F0F0F0F0F0F0F0F,,0F0F0F0FFFFFFFFF,,00000000F0F0F0F,
570 DATA 0F0F0F0F0F0F0F0F,0F0F0F0F,00000000F0F0F0F,,FFFFFFFF0F0F0F0F,,F0F0F0F,,000000000F0F0F0F,,F0F0F0F0F0F0F0F,F0F0F0F
580 DATA F0F0F0F0FFFFFFFF,,00000000F0F0F0F,,0F0F0F0F0F0F0F0F,0F0F0F0F,F0F0F0F,,FFFFFFFF,,F0F0F0F0F0F0F0F0,,,0F0F0F0F,F0F0F0F0F0F0F0F,F0F0F0F
590 DATA 00000000FFFFFFFF,,F0F0F0F0F0F0F0F0,,0F0F0F0F0F0F0F0F,0F0F0F0F,,F0F0F0F,FFFFFFFFF0F0F0F,,F0F0F0F,,0F0F0F0F,,F0F0F0F0F0F0F0F,F0F0F0F
600 CALL KEY(0,M,W) :: IF W<>1 THEN 600 :: GOTO 200
