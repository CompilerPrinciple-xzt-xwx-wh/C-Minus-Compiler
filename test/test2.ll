; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@3 = private unnamed_addr constant [5 x i8] c"%d%d\00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@5 = private unnamed_addr constant [24 x i8] c"Incompatible Dimensions\00", align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str = constant [4 x i8] c"%s\0A\00"
@7 = private unnamed_addr constant [5 x i8] c"%10d\00", align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.1 = constant [4 x i8] c"%s\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entrypoint:
  %k = alloca i32
  %C = alloca [25 x [25 x i32]]
  %num = alloca i32
  %B = alloca [25 x [25 x i32]]
  %A = alloca [25 x [25 x i32]]
  %j = alloca i32
  %i = alloca i32
  %n2 = alloca i32
  %m2 = alloca i32
  %n1 = alloca i32
  %m1 = alloca i32
  %input = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* %m1)
  %input1 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %n1)
  store i32 0, i32* %i
  br label %cond

cond:                                             ; preds = %afterLoop5, %entrypoint
  %tmpvar = load i32, i32* %i
  %tmpvar2 = load i32, i32* %m1
  %icmptmp = icmp slt i32 %tmpvar, %tmpvar2
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  store i32 0, i32* %j
  br label %cond3

afterLoop:                                        ; preds = %cond
  %input18 = call i32 (...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @3, i32 0, i32 0), i32* %m2, i32* %n2)
  store i32 0, i32* %i
  br label %cond19

cond3:                                            ; preds = %loop4, %loop
  %tmpvar6 = load i32, i32* %j
  %tmpvar7 = load i32, i32* %n1
  %icmptmp8 = icmp slt i32 %tmpvar6, %tmpvar7
  %whileCond9 = icmp ne i1 %icmptmp8, false
  br i1 %whileCond9, label %loop4, label %afterLoop5

loop4:                                            ; preds = %cond3
  %input10 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32* %num)
  %tmpvar11 = load i32, i32* %i
  %tmpvar12 = load i32, i32* %j
  %tmparr = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %A, i32 0, i32 %tmpvar11
  %tmpvar13 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr, i32 0, i32 %tmpvar12
  %tmpvar14 = load i32, i32* %num
  store i32 %tmpvar14, i32* %tmpvar13
  %tmpvar15 = load i32, i32* %j
  %addtmpi = add i32 %tmpvar15, 1
  store i32 %addtmpi, i32* %j
  br label %cond3

afterLoop5:                                       ; preds = %cond3
  %tmpvar16 = load i32, i32* %i
  %addtmpi17 = add i32 %tmpvar16, 1
  store i32 %addtmpi17, i32* %i
  br label %cond

cond19:                                           ; preds = %afterLoop28, %afterLoop
  %tmpvar22 = load i32, i32* %i
  %tmpvar23 = load i32, i32* %m2
  %icmptmp24 = icmp slt i32 %tmpvar22, %tmpvar23
  %whileCond25 = icmp ne i1 %icmptmp24, false
  br i1 %whileCond25, label %loop20, label %afterLoop21

loop20:                                           ; preds = %cond19
  store i32 0, i32* %j
  br label %cond26

afterLoop21:                                      ; preds = %cond19
  %tmpvar43 = load i32, i32* %n1
  %tmpvar44 = load i32, i32* %m2
  %icmptmp45 = icmp ne i32 %tmpvar43, %tmpvar44
  %ifCond = icmp ne i1 %icmptmp45, false
  br i1 %ifCond, label %then, label %else

cond26:                                           ; preds = %loop27, %loop20
  %tmpvar29 = load i32, i32* %j
  %tmpvar30 = load i32, i32* %n2
  %icmptmp31 = icmp slt i32 %tmpvar29, %tmpvar30
  %whileCond32 = icmp ne i1 %icmptmp31, false
  br i1 %whileCond32, label %loop27, label %afterLoop28

loop27:                                           ; preds = %cond26
  %input33 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @4, i32 0, i32 0), i32* %num)
  %tmpvar34 = load i32, i32* %i
  %tmpvar35 = load i32, i32* %j
  %tmparr36 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %B, i32 0, i32 %tmpvar34
  %tmpvar37 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr36, i32 0, i32 %tmpvar35
  %tmpvar38 = load i32, i32* %num
  store i32 %tmpvar38, i32* %tmpvar37
  %tmpvar39 = load i32, i32* %j
  %addtmpi40 = add i32 %tmpvar39, 1
  store i32 %addtmpi40, i32* %j
  br label %cond26

afterLoop28:                                      ; preds = %cond26
  %tmpvar41 = load i32, i32* %i
  %addtmpi42 = add i32 %tmpvar41, 1
  store i32 %addtmpi42, i32* %i
  br label %cond19

then:                                             ; preds = %afterLoop21
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @5, i32 0, i32 0))
  %print = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @6, i32 0, i32 0))
  br label %merge

else:                                             ; preds = %afterLoop21
  store i32 0, i32* %i
  br label %cond46

merge:                                            ; preds = %afterLoop100, %then
  ret i32 0

cond46:                                           ; preds = %afterLoop55, %else
  %tmpvar49 = load i32, i32* %i
  %tmpvar50 = load i32, i32* %m1
  %icmptmp51 = icmp slt i32 %tmpvar49, %tmpvar50
  %whileCond52 = icmp ne i1 %icmptmp51, false
  br i1 %whileCond52, label %loop47, label %afterLoop48

loop47:                                           ; preds = %cond46
  store i32 0, i32* %j
  br label %cond53

afterLoop48:                                      ; preds = %cond46
  store i32 0, i32* %i
  br label %cond98

cond53:                                           ; preds = %afterLoop66, %loop47
  %tmpvar56 = load i32, i32* %j
  %tmpvar57 = load i32, i32* %n2
  %icmptmp58 = icmp slt i32 %tmpvar56, %tmpvar57
  %whileCond59 = icmp ne i1 %icmptmp58, false
  br i1 %whileCond59, label %loop54, label %afterLoop55

loop54:                                           ; preds = %cond53
  %tmpvar60 = load i32, i32* %i
  %tmpvar61 = load i32, i32* %j
  %tmparr62 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %C, i32 0, i32 %tmpvar60
  %tmpvar63 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr62, i32 0, i32 %tmpvar61
  store i32 0, i32* %tmpvar63
  store i32 0, i32* %k
  br label %cond64

afterLoop55:                                      ; preds = %cond53
  %tmpvar96 = load i32, i32* %i
  %addtmpi97 = add i32 %tmpvar96, 1
  store i32 %addtmpi97, i32* %i
  br label %cond46

cond64:                                           ; preds = %loop65, %loop54
  %tmpvar67 = load i32, i32* %k
  %tmpvar68 = load i32, i32* %n1
  %icmptmp69 = icmp slt i32 %tmpvar67, %tmpvar68
  %whileCond70 = icmp ne i1 %icmptmp69, false
  br i1 %whileCond70, label %loop65, label %afterLoop66

loop65:                                           ; preds = %cond64
  %tmpvar71 = load i32, i32* %i
  %tmpvar72 = load i32, i32* %j
  %tmparr73 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %C, i32 0, i32 %tmpvar71
  %tmpvar74 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr73, i32 0, i32 %tmpvar72
  %tmpvar75 = load i32, i32* %i
  %tmpvar76 = load i32, i32* %j
  %tmparr77 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %C, i32 0, i32 %tmpvar75
  %tmpvar78 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr77, i32 0, i32 %tmpvar76
  %tmpvar79 = load i32, i32* %tmpvar78
  %tmpvar80 = load i32, i32* %i
  %tmpvar81 = load i32, i32* %k
  %tmparr82 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %A, i32 0, i32 %tmpvar80
  %tmpvar83 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr82, i32 0, i32 %tmpvar81
  %tmpvar84 = load i32, i32* %tmpvar83
  %tmpvar85 = load i32, i32* %k
  %tmpvar86 = load i32, i32* %j
  %tmparr87 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %B, i32 0, i32 %tmpvar85
  %tmpvar88 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr87, i32 0, i32 %tmpvar86
  %tmpvar89 = load i32, i32* %tmpvar88
  %addtmpi90 = mul i32 %tmpvar84, %tmpvar89
  %addtmpi91 = add i32 %tmpvar79, %addtmpi90
  store i32 %addtmpi91, i32* %tmpvar74
  %tmpvar92 = load i32, i32* %k
  %addtmpi93 = add i32 %tmpvar92, 1
  store i32 %addtmpi93, i32* %k
  br label %cond64

afterLoop66:                                      ; preds = %cond64
  %tmpvar94 = load i32, i32* %j
  %addtmpi95 = add i32 %tmpvar94, 1
  store i32 %addtmpi95, i32* %j
  br label %cond53

cond98:                                           ; preds = %afterLoop107, %afterLoop48
  %tmpvar101 = load i32, i32* %i
  %tmpvar102 = load i32, i32* %m1
  %icmptmp103 = icmp slt i32 %tmpvar101, %tmpvar102
  %whileCond104 = icmp ne i1 %icmptmp103, false
  br i1 %whileCond104, label %loop99, label %afterLoop100

loop99:                                           ; preds = %cond98
  store i32 0, i32* %j
  br label %cond105

afterLoop100:                                     ; preds = %cond98
  br label %merge

cond105:                                          ; preds = %loop106, %loop99
  %tmpvar108 = load i32, i32* %j
  %tmpvar109 = load i32, i32* %n2
  %icmptmp110 = icmp slt i32 %tmpvar108, %tmpvar109
  %whileCond111 = icmp ne i1 %icmptmp110, false
  br i1 %whileCond111, label %loop106, label %afterLoop107

loop106:                                          ; preds = %cond105
  %tmpvar112 = load i32, i32* %i
  %tmpvar113 = load i32, i32* %j
  %tmparr114 = getelementptr inbounds [25 x [25 x i32]], [25 x [25 x i32]]* %C, i32 0, i32 %tmpvar112
  %tmpvar115 = getelementptr inbounds [25 x i32], [25 x i32]* %tmparr114, i32 0, i32 %tmpvar113
  %tmpvar116 = load i32, i32* %tmpvar115
  %printf117 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @7, i32 0, i32 0), i32 %tmpvar116)
  %tmpvar118 = load i32, i32* %j
  %addtmpi119 = add i32 %tmpvar118, 1
  store i32 %addtmpi119, i32* %j
  br label %cond105

afterLoop107:                                     ; preds = %cond105
  %print120 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @8, i32 0, i32 0))
  %tmpvar121 = load i32, i32* %i
  %addtmpi122 = add i32 %tmpvar121, 1
  store i32 %addtmpi122, i32* %i
  br label %cond98
}
