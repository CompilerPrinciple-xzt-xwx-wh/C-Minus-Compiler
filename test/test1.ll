; ModuleID = 'main'
source_filename = "main"

@array = private global [10000 x i32] zeroinitializer
@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str = constant [4 x i8] c"%s\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @partition(i32 %left, i32 %right) {
entrypoint:
  %temp = alloca i32
  %j = alloca i32
  %i = alloca i32
  %pivot = alloca i32
  %addtmpi = add i32 %left, %right
  %addtmpi1 = sdiv i32 %addtmpi, 2
  %tmpvar = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %addtmpi1
  %tmpvar2 = load i32, i32* %tmpvar
  store i32 %tmpvar2, i32* %pivot
  store i32 %left, i32* %i
  store i32 %right, i32* %j
  br label %cond

cond:                                             ; preds = %merge, %entrypoint
  %tmpvar3 = load i32, i32* %i
  %tmpvar4 = load i32, i32* %j
  %icmptmp = icmp sle i32 %tmpvar3, %tmpvar4
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  br label %cond5

afterLoop:                                        ; preds = %cond
  %tmpvar45 = load i32, i32* %i
  %addtmpi46 = sub i32 %tmpvar45, 1
  ret i32 %addtmpi46

cond5:                                            ; preds = %loop6, %loop
  %tmpvar8 = load i32, i32* %i
  %tmpvar9 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar8
  %tmpvar10 = load i32, i32* %tmpvar9
  %tmpvar11 = load i32, i32* %pivot
  %icmptmp12 = icmp slt i32 %tmpvar10, %tmpvar11
  %whileCond13 = icmp ne i1 %icmptmp12, false
  br i1 %whileCond13, label %loop6, label %afterLoop7

loop6:                                            ; preds = %cond5
  %tmpvar14 = load i32, i32* %i
  %addtmpi15 = add i32 %tmpvar14, 1
  store i32 %addtmpi15, i32* %i
  br label %cond5

afterLoop7:                                       ; preds = %cond5
  br label %cond16

cond16:                                           ; preds = %loop17, %afterLoop7
  %tmpvar19 = load i32, i32* %j
  %tmpvar20 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar19
  %tmpvar21 = load i32, i32* %tmpvar20
  %tmpvar22 = load i32, i32* %pivot
  %icmptmp23 = icmp sgt i32 %tmpvar21, %tmpvar22
  %whileCond24 = icmp ne i1 %icmptmp23, false
  br i1 %whileCond24, label %loop17, label %afterLoop18

loop17:                                           ; preds = %cond16
  %tmpvar25 = load i32, i32* %j
  %addtmpi26 = sub i32 %tmpvar25, 1
  store i32 %addtmpi26, i32* %j
  br label %cond16

afterLoop18:                                      ; preds = %cond16
  %tmpvar27 = load i32, i32* %i
  %tmpvar28 = load i32, i32* %j
  %icmptmp29 = icmp sle i32 %tmpvar27, %tmpvar28
  %ifCond = icmp ne i1 %icmptmp29, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %afterLoop18
  %tmpvar30 = load i32, i32* %i
  %tmpvar31 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar30
  %tmpvar32 = load i32, i32* %tmpvar31
  store i32 %tmpvar32, i32* %temp
  %tmpvar33 = load i32, i32* %i
  %tmpvar34 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar33
  %tmpvar35 = load i32, i32* %j
  %tmpvar36 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar35
  %tmpvar37 = load i32, i32* %tmpvar36
  store i32 %tmpvar37, i32* %tmpvar34
  %tmpvar38 = load i32, i32* %j
  %tmpvar39 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar38
  %tmpvar40 = load i32, i32* %temp
  store i32 %tmpvar40, i32* %tmpvar39
  %tmpvar41 = load i32, i32* %i
  %addtmpi42 = add i32 %tmpvar41, 1
  store i32 %addtmpi42, i32* %i
  %tmpvar43 = load i32, i32* %j
  %addtmpi44 = sub i32 %tmpvar43, 1
  store i32 %addtmpi44, i32* %j
  br label %merge

else:                                             ; preds = %afterLoop18
  br label %merge

merge:                                            ; preds = %else, %then
  br label %cond
}

define i32 @sort(i32 %left, i32 %right) {
entrypoint:
  %ppp = alloca i32
  %pp = alloca i32
  %p = alloca i32
  %icmptmp = icmp slt i32 %left, %right
  %ifCond = icmp ne i1 %icmptmp, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entrypoint
  %calltmp = call i32 @partition(i32 %left, i32 %right)
  store i32 %calltmp, i32* %p
  %tmpvar = load i32, i32* %p
  %calltmp1 = call i32 @sort(i32 %left, i32 %tmpvar)
  store i32 %calltmp1, i32* %pp
  %tmpvar2 = load i32, i32* %p
  %addtmpi = add i32 %tmpvar2, 1
  %calltmp3 = call i32 @sort(i32 %addtmpi, i32 %right)
  store i32 %calltmp3, i32* %ppp
  br label %merge

else:                                             ; preds = %entrypoint
  br label %merge

merge:                                            ; preds = %else, %then
  ret i32 2
}

define i32 @main() {
entrypoint:
  %pppp = alloca i32
  %num = alloca i32
  %i = alloca i32
  %N = alloca i32
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* %N)
  store i32 0, i32* %i
  br label %cond

cond:                                             ; preds = %loop, %entrypoint
  %tmpvar = load i32, i32* %i
  %tmpvar1 = load i32, i32* %N
  %icmptmp = icmp slt i32 %tmpvar, %tmpvar1
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %scanf2 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %num)
  %tmpvar3 = load i32, i32* %i
  %tmpvar4 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar3
  %tmpvar5 = load i32, i32* %num
  store i32 %tmpvar5, i32* %tmpvar4
  %tmpvar6 = load i32, i32* %i
  %addtmpi = add i32 %tmpvar6, 1
  store i32 %addtmpi, i32* %i
  br label %cond

afterLoop:                                        ; preds = %cond
  %tmpvar7 = load i32, i32* %N
  %addtmpi8 = sub i32 %tmpvar7, 1
  %calltmp = call i32 @sort(i32 0, i32 %addtmpi8)
  store i32 %calltmp, i32* %pppp
  store i32 0, i32* %i
  br label %cond9

cond9:                                            ; preds = %loop10, %afterLoop
  %tmpvar12 = load i32, i32* %i
  %tmpvar13 = load i32, i32* %N
  %icmptmp14 = icmp slt i32 %tmpvar12, %tmpvar13
  %whileCond15 = icmp ne i1 %icmptmp14, false
  br i1 %whileCond15, label %loop10, label %afterLoop11

loop10:                                           ; preds = %cond9
  %tmpvar16 = load i32, i32* %i
  %tmpvar17 = getelementptr inbounds [10000 x i32], [10000 x i32]* @array, i32 0, i32 %tmpvar16
  %tmpvar18 = load i32, i32* %tmpvar17
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32 %tmpvar18)
  %print = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @3, i32 0, i32 0))
  %tmpvar19 = load i32, i32* %i
  %addtmpi20 = add i32 %tmpvar19, 1
  store i32 %addtmpi20, i32* %i
  br label %cond9

afterLoop11:                                      ; preds = %cond9
  ret i32 0
}
