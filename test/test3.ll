; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@3 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@5 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@6 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@7 = private unnamed_addr constant [10 x i8] c"GPA: %.1f\00", align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str = constant [4 x i8] c"%s\0A\00"
@9 = private unnamed_addr constant [20 x i8] c"Hours Attempted: %d\00", align 1
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.1 = constant [4 x i8] c"%s\0A\00"
@11 = private unnamed_addr constant [20 x i8] c"Hours Completed: %d\00", align 1
@12 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.2 = constant [4 x i8] c"%s\0A\00"
@13 = private unnamed_addr constant [22 x i8] c"Credits Remaining: %d\00", align 1
@14 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.3 = constant [4 x i8] c"%s\0A\00"
@15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.4 = constant [4 x i8] c"%s\0A\00"
@16 = private unnamed_addr constant [30 x i8] c"Possible Courses to Take Next\00", align 1
@17 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.5 = constant [4 x i8] c"%s\0A\00"
@18 = private unnamed_addr constant [26 x i8] c"  None - Congratulations!\00", align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.6 = constant [4 x i8] c"%s\0A\00"
@20 = private unnamed_addr constant [3 x i8] c"  \00", align 1
@21 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@22 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.7 = constant [4 x i8] c"%s\0A\00"
@23 = private unnamed_addr constant [3 x i8] c"  \00", align 1
@24 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@25 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.8 = constant [4 x i8] c"%s\0A\00"
@26 = private unnamed_addr constant [3 x i8] c"  \00", align 1
@27 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@28 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.9 = constant [4 x i8] c"%s\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entrypoint:
  %p = alloca i32
  %innerflag = alloca i32
  %n = alloca i32
  %m = alloca i32
  %flagnum = alloca i32
  %num = alloca i32
  %l = alloca i32
  %k = alloca i32
  %precourseset = alloca [100 x i8]
  %precourseterm = alloca [5 x i8]
  %q = alloca i32
  %pp = alloca i32
  %cnt = alloca i32
  %remainIndex = alloca [100 x i32]
  %GPA = alloca float
  %creditsRemain = alloca i32
  %creditsCompleted = alloca i32
  %creditsAttempted = alloca i32
  %coursenum = alloca i32
  %crd = alloca i32
  %ch = alloca i8
  %j = alloca i32
  %i = alloca i32
  %credit = alloca [100 x i32]
  %grade = alloca [100 x i8]
  %precourse = alloca [100 x [1000 x i8]]
  %course = alloca [100 x [5 x i8]]
  store i32 0, i32* %i
  store i32 0, i32* %j
  br label %cond

cond:                                             ; preds = %merge59, %entrypoint
  br i1 true, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i8* %ch)
  store i32 0, i32* %j
  %tmpvar = load i8, i8* %ch
  %icmptmp = icmp eq i8 %tmpvar, 10
  %ifCond = icmp ne i1 %icmptmp, false
  br i1 %ifCond, label %then, label %else

afterLoop:                                        ; preds = %then, %cond
  %tmpvar68 = load i32, i32* %i
  store i32 %tmpvar68, i32* %coursenum
  store i32 0, i32* %creditsAttempted
  store i32 0, i32* %creditsCompleted
  store i32 0, i32* %creditsRemain
  store float 0.000000e+00, float* %GPA
  store i32 0, i32* %cnt
  store i32 0, i32* %i
  br label %cond69

then:                                             ; preds = %loop
  br label %afterLoop
  br label %merge

else:                                             ; preds = %loop
  %tmpvar1 = load i32, i32* %i
  %tmpvar2 = load i32, i32* %j
  %tmparr = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar1
  %tmpvar3 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr, i32 0, i32 %tmpvar2
  %tmpvar4 = load i8, i8* %ch
  store i8 %tmpvar4, i8* %tmpvar3
  %tmpvar5 = load i32, i32* %j
  %addtmpi = add i32 %tmpvar5, 1
  store i32 %addtmpi, i32* %j
  br label %merge

merge:                                            ; preds = %else, %then
  br label %cond6

cond6:                                            ; preds = %merge15, %merge
  br i1 true, label %loop7, label %afterLoop8

loop7:                                            ; preds = %cond6
  %scanf9 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i8* %ch)
  %tmpvar10 = load i8, i8* %ch
  %icmptmp11 = icmp eq i8 %tmpvar10, 124
  %ifCond12 = icmp ne i1 %icmptmp11, false
  br i1 %ifCond12, label %then13, label %else14

afterLoop8:                                       ; preds = %then13, %cond6
  %scanf27 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32* %crd)
  %tmpvar28 = load i32, i32* %i
  %tmpvar29 = getelementptr inbounds [100 x i32], [100 x i32]* %credit, i32 0, i32 %tmpvar28
  %tmpvar30 = load i32, i32* %crd
  store i32 %tmpvar30, i32* %tmpvar29
  store i32 0, i32* %j
  %scanf31 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @3, i32 0, i32 0), i8* %ch)
  br label %cond32

then13:                                           ; preds = %loop7
  %tmpvar16 = load i32, i32* %i
  %tmpvar17 = load i32, i32* %j
  %tmparr18 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar16
  %tmpvar19 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr18, i32 0, i32 %tmpvar17
  store i8 0, i8* %tmpvar19
  br label %afterLoop8
  br label %merge15

else14:                                           ; preds = %loop7
  %tmpvar20 = load i32, i32* %i
  %tmpvar21 = load i32, i32* %j
  %tmparr22 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar20
  %tmpvar23 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr22, i32 0, i32 %tmpvar21
  %tmpvar24 = load i8, i8* %ch
  store i8 %tmpvar24, i8* %tmpvar23
  %tmpvar25 = load i32, i32* %j
  %addtmpi26 = add i32 %tmpvar25, 1
  store i32 %addtmpi26, i32* %j
  br label %merge15

merge15:                                          ; preds = %else14, %then13
  br label %cond6

cond32:                                           ; preds = %merge41, %afterLoop8
  br i1 true, label %loop33, label %afterLoop34

loop33:                                           ; preds = %cond32
  %scanf35 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @4, i32 0, i32 0), i8* %ch)
  %tmpvar36 = load i8, i8* %ch
  %icmptmp37 = icmp eq i8 %tmpvar36, 124
  %ifCond38 = icmp ne i1 %icmptmp37, false
  br i1 %ifCond38, label %then39, label %else40

afterLoop34:                                      ; preds = %then39, %cond32
  %scanf53 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @5, i32 0, i32 0), i8* %ch)
  %tmpvar54 = load i8, i8* %ch
  %icmptmp55 = icmp eq i8 %tmpvar54, 10
  %ifCond56 = icmp ne i1 %icmptmp55, false
  br i1 %ifCond56, label %then57, label %else58

then39:                                           ; preds = %loop33
  %tmpvar42 = load i32, i32* %i
  %tmpvar43 = load i32, i32* %j
  %tmparr44 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar42
  %tmpvar45 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr44, i32 0, i32 %tmpvar43
  store i8 0, i8* %tmpvar45
  br label %afterLoop34
  br label %merge41

else40:                                           ; preds = %loop33
  %tmpvar46 = load i32, i32* %i
  %tmpvar47 = load i32, i32* %j
  %tmparr48 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar46
  %tmpvar49 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr48, i32 0, i32 %tmpvar47
  %tmpvar50 = load i8, i8* %ch
  store i8 %tmpvar50, i8* %tmpvar49
  %tmpvar51 = load i32, i32* %j
  %addtmpi52 = add i32 %tmpvar51, 1
  store i32 %addtmpi52, i32* %j
  br label %merge41

merge41:                                          ; preds = %else40, %then39
  br label %cond32

then57:                                           ; preds = %afterLoop34
  %tmpvar60 = load i32, i32* %i
  %tmpvar61 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar60
  store i8 0, i8* %tmpvar61
  br label %merge59

else58:                                           ; preds = %afterLoop34
  %tmpvar62 = load i32, i32* %i
  %tmpvar63 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar62
  %tmpvar64 = load i8, i8* %ch
  store i8 %tmpvar64, i8* %tmpvar63
  %scanf65 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @6, i32 0, i32 0), i8* %ch)
  br label %merge59

merge59:                                          ; preds = %else58, %then57
  %tmpvar66 = load i32, i32* %i
  %addtmpi67 = add i32 %tmpvar66, 1
  store i32 %addtmpi67, i32* %i
  br label %cond

cond69:                                           ; preds = %merge82, %afterLoop
  %tmpvar72 = load i32, i32* %i
  %tmpvar73 = load i32, i32* %coursenum
  %icmptmp74 = icmp slt i32 %tmpvar72, %tmpvar73
  %whileCond = icmp ne i1 %icmptmp74, false
  br i1 %whileCond, label %loop70, label %afterLoop71

loop70:                                           ; preds = %cond69
  %tmpvar75 = load i32, i32* %i
  %tmpvar76 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar75
  %tmpvar77 = load i8, i8* %tmpvar76
  %icmptmp78 = icmp ne i8 %tmpvar77, 0
  %ifCond79 = icmp ne i1 %icmptmp78, false
  br i1 %ifCond79, label %then80, label %else81

afterLoop71:                                      ; preds = %cond69
  %tmpvar128 = load float, float* %GPA
  %fcmptmp = fcmp one float %tmpvar128, 0.000000e+00
  %ifCond129 = icmp ne i1 %fcmptmp, false
  br i1 %ifCond129, label %then130, label %else131

then80:                                           ; preds = %loop70
  %tmpvar83 = load i32, i32* %i
  %tmpvar84 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar83
  %tmpvar85 = load i8, i8* %tmpvar84
  %icmptmp86 = icmp ne i8 %tmpvar85, 70
  %ifCond87 = icmp ne i1 %icmptmp86, false
  br i1 %ifCond87, label %then88, label %else89

else81:                                           ; preds = %loop70
  %tmpvar121 = load i32, i32* %creditsRemain
  %tmpvar122 = load i32, i32* %i
  %tmpvar123 = getelementptr inbounds [100 x i32], [100 x i32]* %credit, i32 0, i32 %tmpvar122
  %tmpvar124 = load i32, i32* %tmpvar123
  %addtmpi125 = add i32 %tmpvar121, %tmpvar124
  store i32 %addtmpi125, i32* %creditsRemain
  br label %merge82

merge82:                                          ; preds = %else81, %merge90
  %tmpvar126 = load i32, i32* %i
  %addtmpi127 = add i32 %tmpvar126, 1
  store i32 %addtmpi127, i32* %i
  br label %cond69

then88:                                           ; preds = %then80
  %tmpvar91 = load i32, i32* %cnt
  %tmpvar92 = getelementptr inbounds [100 x i32], [100 x i32]* %remainIndex, i32 0, i32 %tmpvar91
  %tmpvar93 = load i32, i32* %i
  store i32 %tmpvar93, i32* %tmpvar92
  %tmpvar94 = load i32, i32* %cnt
  %addtmpi95 = add i32 %tmpvar94, 1
  store i32 %addtmpi95, i32* %cnt
  %tmpvar96 = load i32, i32* %creditsCompleted
  %tmpvar97 = load i32, i32* %i
  %tmpvar98 = getelementptr inbounds [100 x i32], [100 x i32]* %credit, i32 0, i32 %tmpvar97
  %tmpvar99 = load i32, i32* %tmpvar98
  %addtmpi100 = add i32 %tmpvar96, %tmpvar99
  store i32 %addtmpi100, i32* %creditsCompleted
  %tmpvar101 = load float, float* %GPA
  %tmpvar102 = load i32, i32* %i
  %tmpvar103 = getelementptr inbounds [100 x i32], [100 x i32]* %credit, i32 0, i32 %tmpvar102
  %tmpvar104 = load i32, i32* %tmpvar103
  %tmpvar105 = load i32, i32* %i
  %tmpvar106 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar105
  %tmpvar107 = load i8, i8* %tmpvar106
  %tmptypecast = zext i8 %tmpvar107 to i32
  %addtmpi108 = sub i32 69, %tmptypecast
  %addtmpi109 = mul i32 %tmpvar104, %addtmpi108
  %tmptypecast110 = sitofp i32 %addtmpi109 to float
  %addtmpf = fadd float %tmpvar101, %tmptypecast110
  store float %addtmpf, float* %GPA
  br label %merge90

else89:                                           ; preds = %then80
  %tmpvar111 = load i32, i32* %creditsRemain
  %tmpvar112 = load i32, i32* %i
  %tmpvar113 = getelementptr inbounds [100 x i32], [100 x i32]* %credit, i32 0, i32 %tmpvar112
  %tmpvar114 = load i32, i32* %tmpvar113
  %addtmpi115 = add i32 %tmpvar111, %tmpvar114
  store i32 %addtmpi115, i32* %creditsRemain
  br label %merge90

merge90:                                          ; preds = %else89, %then88
  %tmpvar116 = load i32, i32* %creditsAttempted
  %tmpvar117 = load i32, i32* %i
  %tmpvar118 = getelementptr inbounds [100 x i32], [100 x i32]* %credit, i32 0, i32 %tmpvar117
  %tmpvar119 = load i32, i32* %tmpvar118
  %addtmpi120 = add i32 %tmpvar116, %tmpvar119
  store i32 %addtmpi120, i32* %creditsAttempted
  br label %merge82

then130:                                          ; preds = %afterLoop71
  %tmpvar133 = load float, float* %GPA
  %tmpvar134 = load i32, i32* %creditsAttempted
  %tmptypecast135 = sitofp i32 %tmpvar134 to float
  %addtmpf136 = fdiv float %tmpvar133, %tmptypecast135
  store float %addtmpf136, float* %GPA
  br label %merge132

else131:                                          ; preds = %afterLoop71
  br label %merge132

merge132:                                         ; preds = %else131, %then130
  %tmpvar137 = load float, float* %GPA
  %tempdouble = fpext float %tmpvar137 to double
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @7, i32 0, i32 0), double %tempdouble)
  %print = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @8, i32 0, i32 0))
  %tmpvar138 = load i32, i32* %creditsAttempted
  %printf139 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @9, i32 0, i32 0), i32 %tmpvar138)
  %print140 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @10, i32 0, i32 0))
  %tmpvar141 = load i32, i32* %creditsCompleted
  %printf142 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @11, i32 0, i32 0), i32 %tmpvar141)
  %print143 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @12, i32 0, i32 0))
  %tmpvar144 = load i32, i32* %creditsRemain
  %printf145 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @13, i32 0, i32 0), i32 %tmpvar144)
  %print146 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @14, i32 0, i32 0))
  %print147 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @15, i32 0, i32 0))
  %printf148 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @16, i32 0, i32 0))
  %print149 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @17, i32 0, i32 0))
  %tmpvar150 = load i32, i32* %creditsRemain
  %icmptmp151 = icmp eq i32 %tmpvar150, 0
  %ifCond152 = icmp ne i1 %icmptmp151, false
  br i1 %ifCond152, label %then153, label %else154

then153:                                          ; preds = %merge132
  %printf156 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @18, i32 0, i32 0))
  %print157 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @19, i32 0, i32 0))
  br label %merge155

else154:                                          ; preds = %merge132
  br label %merge155

merge155:                                         ; preds = %else154, %then153
  %tmpvar158 = load i32, i32* %cnt
  %icmptmp159 = icmp eq i32 %tmpvar158, 0
  %ifCond160 = icmp ne i1 %icmptmp159, false
  br i1 %ifCond160, label %then161, label %else162

then161:                                          ; preds = %merge155
  store i32 0, i32* %pp
  br label %cond164

else162:                                          ; preds = %merge155
  br label %merge163

merge163:                                         ; preds = %else162, %afterLoop166
  store i32 0, i32* %i
  br label %cond202

cond164:                                          ; preds = %merge179, %then161
  %tmpvar167 = load i32, i32* %pp
  %tmpvar168 = load i32, i32* %coursenum
  %icmptmp169 = icmp slt i32 %tmpvar167, %tmpvar168
  %whileCond170 = icmp ne i1 %icmptmp169, false
  br i1 %whileCond170, label %loop165, label %afterLoop166

loop165:                                          ; preds = %cond164
  %tmpvar171 = load i32, i32* %pp
  %tmparr172 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar171
  %tmpvar173 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr172, i32 0, i32 0
  %tmpvar174 = load i8, i8* %tmpvar173
  %icmptmp175 = icmp eq i8 %tmpvar174, 0
  %ifCond176 = icmp ne i1 %icmptmp175, false
  br i1 %ifCond176, label %then177, label %else178

afterLoop166:                                     ; preds = %cond164
  br label %merge163

then177:                                          ; preds = %loop165
  store i32 0, i32* %q
  %printf180 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @20, i32 0, i32 0))
  br label %cond181

else178:                                          ; preds = %loop165
  br label %merge179

merge179:                                         ; preds = %else178, %afterLoop183
  %tmpvar200 = load i32, i32* %pp
  %addtmpi201 = add i32 %tmpvar200, 1
  store i32 %addtmpi201, i32* %pp
  br label %cond164

cond181:                                          ; preds = %loop182, %then177
  %tmpvar184 = load i32, i32* %pp
  %tmpvar185 = load i32, i32* %q
  %tmparr186 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar184
  %tmpvar187 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr186, i32 0, i32 %tmpvar185
  %tmpvar188 = load i8, i8* %tmpvar187
  %icmptmp189 = icmp ne i8 %tmpvar188, 0
  %whileCond190 = icmp ne i1 %icmptmp189, false
  br i1 %whileCond190, label %loop182, label %afterLoop183

loop182:                                          ; preds = %cond181
  %tmpvar191 = load i32, i32* %pp
  %tmpvar192 = load i32, i32* %q
  %tmparr193 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar191
  %tmpvar194 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr193, i32 0, i32 %tmpvar192
  %tmpvar195 = load i8, i8* %tmpvar194
  %printf196 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @21, i32 0, i32 0), i8 %tmpvar195)
  %tmpvar197 = load i32, i32* %q
  %addtmpi198 = add i32 %tmpvar197, 1
  store i32 %addtmpi198, i32* %q
  br label %cond181

afterLoop183:                                     ; preds = %cond181
  %print199 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @22, i32 0, i32 0))
  br label %merge179

cond202:                                          ; preds = %merge226, %merge163
  %tmpvar205 = load i32, i32* %i
  %tmpvar206 = load i32, i32* %coursenum
  %icmptmp207 = icmp slt i32 %tmpvar205, %tmpvar206
  %whileCond208 = icmp ne i1 %icmptmp207, false
  br i1 %whileCond208, label %loop203, label %afterLoop204

loop203:                                          ; preds = %cond202
  %tmpvar209 = load i32, i32* %cnt
  %icmptmp210 = icmp eq i32 %tmpvar209, 0
  %ifCond211 = icmp ne i1 %icmptmp210, false
  br i1 %ifCond211, label %then212, label %else213

afterLoop204:                                     ; preds = %then212, %cond202
  ret i32 0

then212:                                          ; preds = %loop203
  br label %afterLoop204
  br label %merge214

else213:                                          ; preds = %loop203
  br label %merge214

merge214:                                         ; preds = %else213, %then212
  %tmpvar215 = load i32, i32* %i
  %tmpvar216 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar215
  %tmpvar217 = load i8, i8* %tmpvar216
  %icmptmp218 = icmp eq i8 %tmpvar217, 70
  %tmpvar219 = load i32, i32* %i
  %tmpvar220 = getelementptr inbounds [100 x i8], [100 x i8]* %grade, i32 0, i32 %tmpvar219
  %tmpvar221 = load i8, i8* %tmpvar220
  %icmptmp222 = icmp eq i8 %tmpvar221, 0
  %tmpAnd = or i1 %icmptmp218, %icmptmp222
  %ifCond223 = icmp ne i1 %tmpAnd, false
  br i1 %ifCond223, label %then224, label %else225

then224:                                          ; preds = %merge214
  %tmpvar227 = load i32, i32* %i
  %tmparr228 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar227
  %tmpvar229 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr228, i32 0, i32 0
  %tmpvar230 = load i8, i8* %tmpvar229
  %icmptmp231 = icmp eq i8 %tmpvar230, 0
  %ifCond232 = icmp ne i1 %icmptmp231, false
  br i1 %ifCond232, label %then233, label %else234

else225:                                          ; preds = %merge214
  br label %merge226

merge226:                                         ; preds = %else225, %merge235
  %tmpvar435 = load i32, i32* %i
  %addtmpi436 = add i32 %tmpvar435, 1
  store i32 %addtmpi436, i32* %i
  br label %cond202

then233:                                          ; preds = %then224
  store i32 0, i32* %j
  %printf236 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @23, i32 0, i32 0))
  br label %cond237

else234:                                          ; preds = %then224
  store i32 0, i32* %j
  store i32 0, i32* %k
  br label %cond256

merge235:                                         ; preds = %afterLoop258, %afterLoop239
  br label %merge226

cond237:                                          ; preds = %loop238, %then233
  %tmpvar240 = load i32, i32* %i
  %tmpvar241 = load i32, i32* %j
  %tmparr242 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar240
  %tmpvar243 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr242, i32 0, i32 %tmpvar241
  %tmpvar244 = load i8, i8* %tmpvar243
  %icmptmp245 = icmp ne i8 %tmpvar244, 0
  %whileCond246 = icmp ne i1 %icmptmp245, false
  br i1 %whileCond246, label %loop238, label %afterLoop239

loop238:                                          ; preds = %cond237
  %tmpvar247 = load i32, i32* %i
  %tmpvar248 = load i32, i32* %j
  %tmparr249 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar247
  %tmpvar250 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr249, i32 0, i32 %tmpvar248
  %tmpvar251 = load i8, i8* %tmpvar250
  %printf252 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @24, i32 0, i32 0), i8 %tmpvar251)
  %tmpvar253 = load i32, i32* %j
  %addtmpi254 = add i32 %tmpvar253, 1
  store i32 %addtmpi254, i32* %j
  br label %cond237

afterLoop239:                                     ; preds = %cond237
  %print255 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @25, i32 0, i32 0))
  br label %merge235

cond256:                                          ; preds = %merge275, %else234
  br i1 true, label %loop257, label %afterLoop258

loop257:                                          ; preds = %cond256
  %tmpvar259 = load i32, i32* %i
  %tmpvar260 = load i32, i32* %j
  %tmparr261 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar259
  %tmpvar262 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr261, i32 0, i32 %tmpvar260
  %tmpvar263 = load i8, i8* %tmpvar262
  %icmptmp264 = icmp eq i8 %tmpvar263, 59
  %tmpvar265 = load i32, i32* %i
  %tmpvar266 = load i32, i32* %j
  %tmparr267 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar265
  %tmpvar268 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr267, i32 0, i32 %tmpvar266
  %tmpvar269 = load i8, i8* %tmpvar268
  %icmptmp270 = icmp eq i8 %tmpvar269, 0
  %tmpAnd271 = or i1 %icmptmp264, %icmptmp270
  %ifCond272 = icmp ne i1 %tmpAnd271, false
  br i1 %ifCond272, label %then273, label %else274

afterLoop258:                                     ; preds = %then421, %afterLoop394, %cond256
  br label %merge235

then273:                                          ; preds = %loop257
  %tmpvar276 = load i32, i32* %k
  %tmpvar277 = getelementptr inbounds [100 x i8], [100 x i8]* %precourseset, i32 0, i32 %tmpvar276
  store i8 0, i8* %tmpvar277
  store i32 0, i32* %k
  store i32 0, i32* %l
  store i32 0, i32* %num
  store i32 0, i32* %flagnum
  br label %cond278

else274:                                          ; preds = %loop257
  br label %merge275

merge275:                                         ; preds = %else274, %merge423
  %tmpvar424 = load i32, i32* %k
  %tmpvar425 = getelementptr inbounds [100 x i8], [100 x i8]* %precourseset, i32 0, i32 %tmpvar424
  %tmpvar426 = load i32, i32* %i
  %tmpvar427 = load i32, i32* %j
  %tmparr428 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar426
  %tmpvar429 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr428, i32 0, i32 %tmpvar427
  %tmpvar430 = load i8, i8* %tmpvar429
  store i8 %tmpvar430, i8* %tmpvar425
  %tmpvar431 = load i32, i32* %j
  %addtmpi432 = add i32 %tmpvar431, 1
  store i32 %addtmpi432, i32* %j
  %tmpvar433 = load i32, i32* %k
  %addtmpi434 = add i32 %tmpvar433, 1
  store i32 %addtmpi434, i32* %k
  br label %cond256

cond278:                                          ; preds = %merge293, %then273
  br i1 true, label %loop279, label %afterLoop280

loop279:                                          ; preds = %cond278
  %tmpvar281 = load i32, i32* %k
  %tmpvar282 = getelementptr inbounds [100 x i8], [100 x i8]* %precourseset, i32 0, i32 %tmpvar281
  %tmpvar283 = load i8, i8* %tmpvar282
  %icmptmp284 = icmp eq i8 %tmpvar283, 44
  %tmpvar285 = load i32, i32* %k
  %tmpvar286 = getelementptr inbounds [100 x i8], [100 x i8]* %precourseset, i32 0, i32 %tmpvar285
  %tmpvar287 = load i8, i8* %tmpvar286
  %icmptmp288 = icmp eq i8 %tmpvar287, 0
  %tmpAnd289 = or i1 %icmptmp284, %icmptmp288
  %ifCond290 = icmp ne i1 %tmpAnd289, false
  br i1 %ifCond290, label %then291, label %else292

afterLoop280:                                     ; preds = %then372, %cond278
  %tmpvar384 = load i32, i32* %num
  %tmpvar385 = load i32, i32* %flagnum
  %icmptmp386 = icmp eq i32 %tmpvar384, %tmpvar385
  %ifCond387 = icmp ne i1 %icmptmp386, false
  br i1 %ifCond387, label %then388, label %else389

then291:                                          ; preds = %loop279
  %tmpvar294 = load i32, i32* %l
  %tmpvar295 = getelementptr inbounds [5 x i8], [5 x i8]* %precourseterm, i32 0, i32 %tmpvar294
  store i8 0, i8* %tmpvar295
  store i32 0, i32* %m
  store i32 0, i32* %n
  store i32 0, i32* %m
  br label %cond296

else292:                                          ; preds = %loop279
  br label %merge293

merge293:                                         ; preds = %else292, %merge374
  %tmpvar375 = load i32, i32* %l
  %tmpvar376 = getelementptr inbounds [5 x i8], [5 x i8]* %precourseterm, i32 0, i32 %tmpvar375
  %tmpvar377 = load i32, i32* %k
  %tmpvar378 = getelementptr inbounds [100 x i8], [100 x i8]* %precourseset, i32 0, i32 %tmpvar377
  %tmpvar379 = load i8, i8* %tmpvar378
  store i8 %tmpvar379, i8* %tmpvar376
  %tmpvar380 = load i32, i32* %l
  %addtmpi381 = add i32 %tmpvar380, 1
  store i32 %addtmpi381, i32* %l
  %tmpvar382 = load i32, i32* %k
  %addtmpi383 = add i32 %tmpvar382, 1
  store i32 %addtmpi383, i32* %k
  br label %cond278

cond296:                                          ; preds = %merge345, %then291
  %tmpvar299 = load i32, i32* %m
  %tmpvar300 = load i32, i32* %cnt
  %icmptmp301 = icmp slt i32 %tmpvar299, %tmpvar300
  %whileCond302 = icmp ne i1 %icmptmp301, false
  br i1 %whileCond302, label %loop297, label %afterLoop298

loop297:                                          ; preds = %cond296
  store i32 1, i32* %innerflag
  store i32 0, i32* %n
  br label %cond303

afterLoop298:                                     ; preds = %then343, %cond296
  %tmpvar348 = load i32, i32* %m
  %tmpvar349 = load i32, i32* %cnt
  %icmptmp350 = icmp eq i32 %tmpvar348, %tmpvar349
  %tmpvar351 = load i32, i32* %innerflag
  %icmptmp352 = icmp eq i32 %tmpvar351, 0
  %tmpAnd353 = and i1 %icmptmp350, %icmptmp352
  %ifCond354 = icmp ne i1 %tmpAnd353, false
  br i1 %ifCond354, label %then355, label %else356

cond303:                                          ; preds = %merge325, %loop297
  %tmpvar306 = load i32, i32* %n
  %tmpvar307 = getelementptr inbounds [5 x i8], [5 x i8]* %precourseterm, i32 0, i32 %tmpvar306
  %tmpvar308 = load i8, i8* %tmpvar307
  %icmptmp309 = icmp ne i8 %tmpvar308, 0
  %whileCond310 = icmp ne i1 %icmptmp309, false
  br i1 %whileCond310, label %loop304, label %afterLoop305

loop304:                                          ; preds = %cond303
  %tmpvar311 = load i32, i32* %m
  %tmpvar312 = getelementptr inbounds [100 x i32], [100 x i32]* %remainIndex, i32 0, i32 %tmpvar311
  %tmpvar313 = load i32, i32* %tmpvar312
  %tmpvar314 = load i32, i32* %n
  %tmparr315 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar313
  %tmpvar316 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr315, i32 0, i32 %tmpvar314
  %tmpvar317 = load i8, i8* %tmpvar316
  %tmpvar318 = load i32, i32* %n
  %tmpvar319 = getelementptr inbounds [5 x i8], [5 x i8]* %precourseterm, i32 0, i32 %tmpvar318
  %tmpvar320 = load i8, i8* %tmpvar319
  %icmptmp321 = icmp ne i8 %tmpvar317, %tmpvar320
  %ifCond322 = icmp ne i1 %icmptmp321, false
  br i1 %ifCond322, label %then323, label %else324

afterLoop305:                                     ; preds = %cond303
  %tmpvar328 = load i32, i32* %m
  %tmpvar329 = getelementptr inbounds [100 x i32], [100 x i32]* %remainIndex, i32 0, i32 %tmpvar328
  %tmpvar330 = load i32, i32* %tmpvar329
  %tmpvar331 = load i32, i32* %n
  %tmparr332 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar330
  %tmpvar333 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr332, i32 0, i32 %tmpvar331
  %tmpvar334 = load i8, i8* %tmpvar333
  %icmptmp335 = icmp ne i8 %tmpvar334, 0
  %ifCond336 = icmp ne i1 %icmptmp335, false
  br i1 %ifCond336, label %then337, label %else338

then323:                                          ; preds = %loop304
  store i32 0, i32* %innerflag
  br label %merge325

else324:                                          ; preds = %loop304
  br label %merge325

merge325:                                         ; preds = %else324, %then323
  %tmpvar326 = load i32, i32* %n
  %addtmpi327 = add i32 %tmpvar326, 1
  store i32 %addtmpi327, i32* %n
  br label %cond303

then337:                                          ; preds = %afterLoop305
  store i32 0, i32* %innerflag
  br label %merge339

else338:                                          ; preds = %afterLoop305
  br label %merge339

merge339:                                         ; preds = %else338, %then337
  %tmpvar340 = load i32, i32* %innerflag
  %icmptmp341 = icmp eq i32 %tmpvar340, 1
  %ifCond342 = icmp ne i1 %icmptmp341, false
  br i1 %ifCond342, label %then343, label %else344

then343:                                          ; preds = %merge339
  br label %afterLoop298
  br label %merge345

else344:                                          ; preds = %merge339
  br label %merge345

merge345:                                         ; preds = %else344, %then343
  %tmpvar346 = load i32, i32* %m
  %addtmpi347 = add i32 %tmpvar346, 1
  store i32 %addtmpi347, i32* %m
  br label %cond296

then355:                                          ; preds = %afterLoop298
  %tmpvar358 = load i32, i32* %flagnum
  %addtmpi359 = sub i32 %tmpvar358, 1
  store i32 %addtmpi359, i32* %flagnum
  br label %merge357

else356:                                          ; preds = %afterLoop298
  br label %merge357

merge357:                                         ; preds = %else356, %then355
  %tmpvar360 = load i32, i32* %flagnum
  %addtmpi361 = add i32 %tmpvar360, 1
  store i32 %addtmpi361, i32* %flagnum
  %tmpvar362 = load i32, i32* %num
  %addtmpi363 = add i32 %tmpvar362, 1
  store i32 %addtmpi363, i32* %num
  store i32 0, i32* %l
  %tmpvar364 = load i32, i32* %k
  %addtmpi365 = add i32 %tmpvar364, 1
  store i32 %addtmpi365, i32* %k
  %tmpvar366 = load i32, i32* %k
  %addtmpi367 = sub i32 %tmpvar366, 1
  %tmpvar368 = getelementptr inbounds [100 x i8], [100 x i8]* %precourseset, i32 0, i32 %addtmpi367
  %tmpvar369 = load i8, i8* %tmpvar368
  %icmptmp370 = icmp eq i8 %tmpvar369, 0
  %ifCond371 = icmp ne i1 %icmptmp370, false
  br i1 %ifCond371, label %then372, label %else373

then372:                                          ; preds = %merge357
  br label %afterLoop280
  br label %merge374

else373:                                          ; preds = %merge357
  br label %merge374

merge374:                                         ; preds = %else373, %then372
  br label %merge293

then388:                                          ; preds = %afterLoop280
  store i32 0, i32* %p
  %printf391 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @26, i32 0, i32 0))
  br label %cond392

else389:                                          ; preds = %afterLoop280
  br label %merge390

merge390:                                         ; preds = %else389, %afterLoop394
  store i32 0, i32* %k
  %tmpvar411 = load i32, i32* %j
  %addtmpi412 = add i32 %tmpvar411, 1
  store i32 %addtmpi412, i32* %j
  %tmpvar413 = load i32, i32* %i
  %tmpvar414 = load i32, i32* %j
  %addtmpi415 = sub i32 %tmpvar414, 1
  %tmparr416 = getelementptr inbounds [100 x [1000 x i8]], [100 x [1000 x i8]]* %precourse, i32 0, i32 %tmpvar413
  %tmpvar417 = getelementptr inbounds [1000 x i8], [1000 x i8]* %tmparr416, i32 0, i32 %addtmpi415
  %tmpvar418 = load i8, i8* %tmpvar417
  %icmptmp419 = icmp eq i8 %tmpvar418, 0
  %ifCond420 = icmp ne i1 %icmptmp419, false
  br i1 %ifCond420, label %then421, label %else422

cond392:                                          ; preds = %loop393, %then388
  %tmpvar395 = load i32, i32* %i
  %tmpvar396 = load i32, i32* %p
  %tmparr397 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar395
  %tmpvar398 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr397, i32 0, i32 %tmpvar396
  %tmpvar399 = load i8, i8* %tmpvar398
  %icmptmp400 = icmp ne i8 %tmpvar399, 0
  %whileCond401 = icmp ne i1 %icmptmp400, false
  br i1 %whileCond401, label %loop393, label %afterLoop394

loop393:                                          ; preds = %cond392
  %tmpvar402 = load i32, i32* %i
  %tmpvar403 = load i32, i32* %p
  %tmparr404 = getelementptr inbounds [100 x [5 x i8]], [100 x [5 x i8]]* %course, i32 0, i32 %tmpvar402
  %tmpvar405 = getelementptr inbounds [5 x i8], [5 x i8]* %tmparr404, i32 0, i32 %tmpvar403
  %tmpvar406 = load i8, i8* %tmpvar405
  %printf407 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @27, i32 0, i32 0), i8 %tmpvar406)
  %tmpvar408 = load i32, i32* %p
  %addtmpi409 = add i32 %tmpvar408, 1
  store i32 %addtmpi409, i32* %p
  br label %cond392

afterLoop394:                                     ; preds = %cond392
  %print410 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @28, i32 0, i32 0))
  br label %afterLoop258
  br label %merge390

then421:                                          ; preds = %merge390
  br label %afterLoop258
  br label %merge423

else422:                                          ; preds = %merge390
  br label %merge423

merge423:                                         ; preds = %else422, %then421
  br label %merge275
}
