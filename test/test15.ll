; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.timeval = type { i64, i64 }

@llvm.global_ctors = appending global [1 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @before_main, ptr null }]
@llvm.global_dtors = appending global [1 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @after_main, ptr null }]
@.str = private unnamed_addr constant [5 x i8] c"%lld\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.3 = private unnamed_addr constant [6 x i8] c"%lld:\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c" %lld\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c" %lf\00", align 1
@_sysy_us = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_s = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_m = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_h = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_idx = dso_local global i32 0, align 4
@stderr = external global ptr, align 8
@.str.7 = private unnamed_addr constant [35 x i8] c"Timer@%04d-%04d: %dH-%dM-%dS-%dus\0A\00", align 1
@_sysy_l1 = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_l2 = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_start = dso_local global %struct.timeval zeroinitializer, align 8
@_sysy_end = dso_local global %struct.timeval zeroinitializer, align 8

define i64 @main() {
C13:
  %r176 = call ptr @malloc(i64 88)
  %r177 = ptrtoint ptr %r176 to i64
  %r178 = add i64 %r177, 8
  %r179 = sub i64 %r178, 8
  %r180 = inttoptr i64 %r179 to ptr
  store i64 10, ptr %r180, align 8
  %r181 = inttoptr i64 %r178 to ptr
  store i64 2, ptr %r181, align 8
  %r182 = add i64 %r178, 8
  %r183 = inttoptr i64 %r182 to ptr
  store i64 0, ptr %r183, align 8
  %r184 = add i64 %r178, 16
  %r185 = inttoptr i64 %r184 to ptr
  store i64 2, ptr %r185, align 8
  %r186 = add i64 %r178, 24
  %r187 = inttoptr i64 %r186 to ptr
  store i64 3, ptr %r187, align 8
  %r188 = add i64 %r178, 32
  %r189 = inttoptr i64 %r188 to ptr
  store i64 6, ptr %r189, align 8
  %r190 = add i64 %r178, 40
  %r191 = inttoptr i64 %r190 to ptr
  store i64 2, ptr %r191, align 8
  %r192 = add i64 %r178, 48
  %r193 = inttoptr i64 %r192 to ptr
  store i64 5, ptr %r193, align 8
  %r194 = add i64 %r178, 56
  %r195 = inttoptr i64 %r194 to ptr
  store i64 4, ptr %r195, align 8
  %r196 = add i64 %r178, 64
  %r197 = inttoptr i64 %r196 to ptr
  store i64 2, ptr %r197, align 8
  %r198 = add i64 %r178, 72
  %r199 = inttoptr i64 %r198 to ptr
  store i64 8, ptr %r199, align 8
  %r200 = add i64 1, 0
  %r201 = add i64 1, 0
  %r202 = sub i64 %r178, 8
  %r203 = inttoptr i64 %r202 to ptr
  %r204 = load i64, ptr %r203, align 8
  %r205 = call ptr @malloc(i64 168)
  %r206 = ptrtoint ptr %r205 to i64
  %r207 = inttoptr i64 %r206 to ptr
  store i64 20, ptr %r207, align 8
  %r208 = add i64 %r206, 8
  %r209 = add i64 %r208, 0
  %r210 = add i64 %r209, 0
  %r211 = inttoptr i64 %r210 to ptr
  store i64 1, ptr %r211, align 8
  br label %L0

L0:                                               ; preds = %L10, %C13
  %r212 = phi i64 [ %r227, %L10 ], [ %r200, %C13 ]
  %r213 = phi i64 [ %r226, %L10 ], [ %r201, %C13 ]
  %r214 = icmp slt i64 %r212, %r204
  br i1 %r214, label %L11, label %L1

L1:                                               ; preds = %L0
  call void @putint(i64 %r213)
  call void @putch(i64 10)
  ret i64 0

L11:                                              ; preds = %L0
  %r215 = mul i64 %r212, 8
  %r216 = add i64 %r209, %r215
  %r217 = inttoptr i64 %r216 to ptr
  store i64 1, ptr %r217, align 8
  %r218 = add i64 0, 0
  br label %L2

L2:                                               ; preds = %L7, %L11
  %r219 = phi i64 [ %r241, %L7 ], [ %r218, %L11 ]
  %r220 = icmp slt i64 %r219, %r212
  br i1 %r220, label %L8, label %L3

L3:                                               ; preds = %L2
  %r221 = mul i64 %r212, 8
  %r222 = add i64 %r209, %r221
  %r223 = inttoptr i64 %r222 to ptr
  %r224 = load i64, ptr %r223, align 8
  %r225 = icmp sgt i64 %r224, %r213
  br i1 %r225, label %L9, label %L10

L10:                                              ; preds = %L9, %L3
  %r226 = phi i64 [ %r231, %L9 ], [ %r213, %L3 ]
  %r227 = add i64 %r212, 1
  br label %L0

L8:                                               ; preds = %L2
  %r232 = mul i64 %r219, 8
  %r233 = add i64 %r178, %r232
  %r234 = inttoptr i64 %r233 to ptr
  %r235 = load i64, ptr %r234, align 8
  %r236 = mul i64 %r212, 8
  %r237 = add i64 %r178, %r236
  %r238 = inttoptr i64 %r237 to ptr
  %r239 = load i64, ptr %r238, align 8
  %r240 = icmp slt i64 %r235, %r239
  br i1 %r240, label %L6, label %L7

L7:                                               ; preds = %L5, %L8
  %r241 = add i64 %r219, 1
  br label %L2

L6:                                               ; preds = %L8
  %r242 = mul i64 %r219, 8
  %r243 = add i64 %r209, %r242
  %r244 = inttoptr i64 %r243 to ptr
  %r245 = load i64, ptr %r244, align 8
  %r246 = add i64 %r245, 1
  %r247 = mul i64 %r212, 8
  %r248 = add i64 %r209, %r247
  %r249 = inttoptr i64 %r248 to ptr
  %r250 = load i64, ptr %r249, align 8
  %r251 = icmp sgt i64 %r246, %r250
  br i1 %r251, label %L4, label %L5

L5:                                               ; preds = %L4, %L6
  br label %L7

L4:                                               ; preds = %L6
  %r252 = mul i64 %r212, 8
  %r253 = add i64 %r209, %r252
  %r254 = inttoptr i64 %r253 to ptr
  %r255 = mul i64 %r219, 8
  %r256 = add i64 %r209, %r255
  %r257 = inttoptr i64 %r256 to ptr
  %r258 = load i64, ptr %r257, align 8
  %r259 = add i64 %r258, 1
  store i64 %r259, ptr %r254, align 8
  br label %L5

L9:                                               ; preds = %L3
  %r228 = mul i64 %r212, 8
  %r229 = add i64 %r209, %r228
  %r230 = inttoptr i64 %r229 to ptr
  %r231 = load i64, ptr %r230, align 8
  br label %L10
}

declare ptr @malloc(i64)

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @before_main() #0 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  br label %2

2:                                                ; preds = %18, %0
  %3 = load i32, ptr %1, align 4
  %4 = icmp slt i32 %3, 1024
  br i1 %4, label %5, label %21

5:                                                ; preds = %2
  %6 = load i32, ptr %1, align 4
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %7
  store i32 0, ptr %8, align 4
  %9 = load i32, ptr %1, align 4
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %10
  store i32 0, ptr %11, align 4
  %12 = load i32, ptr %1, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %13
  store i32 0, ptr %14, align 4
  %15 = load i32, ptr %1, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %16
  store i32 0, ptr %17, align 4
  br label %18

18:                                               ; preds = %5
  %19 = load i32, ptr %1, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, ptr %1, align 4
  br label %2, !llvm.loop !6

21:                                               ; preds = %2
  store i32 1, ptr @_sysy_idx, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @after_main() #0 {
  %1 = alloca i32, align 4
  store i32 1, ptr %1, align 4
  br label %2

2:                                                ; preds = %63, %0
  %3 = load i32, ptr %1, align 4
  %4 = load i32, ptr @_sysy_idx, align 4
  %5 = icmp slt i32 %3, %4
  br i1 %5, label %6, label %66

6:                                                ; preds = %2
  %7 = load ptr, ptr @stderr, align 8
  %8 = load i32, ptr %1, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [1024 x i32], ptr @_sysy_l1, i64 0, i64 %9
  %11 = load i32, ptr %10, align 4
  %12 = load i32, ptr %1, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [1024 x i32], ptr @_sysy_l2, i64 0, i64 %13
  %15 = load i32, ptr %14, align 4
  %16 = load i32, ptr %1, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %17
  %19 = load i32, ptr %18, align 4
  %20 = load i32, ptr %1, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %21
  %23 = load i32, ptr %22, align 4
  %24 = load i32, ptr %1, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %25
  %27 = load i32, ptr %26, align 4
  %28 = load i32, ptr %1, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %29
  %31 = load i32, ptr %30, align 4
  %32 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %7, ptr noundef getelementptr inbounds ([35 x i8], ptr @.str.7, i64 0, i64 0), i32 noundef %11, i32 noundef %15, i32 noundef %19, i32 noundef %23, i32 noundef %27, i32 noundef %31)
  %33 = load i32, ptr %1, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %34
  %36 = load i32, ptr %35, align 4
  %37 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_us, i64 0, i64 0), align 16
  %38 = add nsw i32 %37, %36
  store i32 %38, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_us, i64 0, i64 0), align 16
  %39 = load i32, ptr %1, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %40
  %42 = load i32, ptr %41, align 4
  %43 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_s, i64 0, i64 0), align 16
  %44 = add nsw i32 %43, %42
  store i32 %44, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_s, i64 0, i64 0), align 16
  %45 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_us, i64 0, i64 0), align 16
  %46 = srem i32 %45, 1000000
  store i32 %46, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_us, i64 0, i64 0), align 16
  %47 = load i32, ptr %1, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %48
  %50 = load i32, ptr %49, align 4
  %51 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_m, i64 0, i64 0), align 16
  %52 = add nsw i32 %51, %50
  store i32 %52, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_m, i64 0, i64 0), align 16
  %53 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_s, i64 0, i64 0), align 16
  %54 = srem i32 %53, 60
  store i32 %54, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_s, i64 0, i64 0), align 16
  %55 = load i32, ptr %1, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %56
  %58 = load i32, ptr %57, align 4
  %59 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_h, i64 0, i64 0), align 16
  %60 = add nsw i32 %59, %58
  store i32 %60, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_h, i64 0, i64 0), align 16
  %61 = load i32, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_m, i64 0, i64 0), align 16
  %62 = srem i32 %61, 60
  store i32 %62, ptr getelementptr inbounds ([1024 x i32], ptr @_sysy_m, i64 0, i64 0), align 16
  br label %63

63:                                               ; preds = %6
  %64 = load i32, ptr %1, align 4
  %65 = add nsw i32 %64, 1
  store i32 %65, ptr %1, align 4
  br label %2, !llvm.loop !8

66:                                               ; preds = %2
  ret void
}

declare i32 @fprintf(ptr noundef, ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @getint() #0 {
  %1 = alloca i64, align 8
  %2 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([5 x i8], ptr @.str, i64 0, i64 0), ptr noundef %1)
  %3 = load i64, ptr %1, align 8
  ret i64 %3
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @getfloat() #0 {
  %1 = alloca double, align 8
  %2 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([4 x i8], ptr @.str.1, i64 0, i64 0), ptr noundef %1)
  %3 = load double, ptr %1, align 8
  ret double %3
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @getch() #0 {
  %1 = alloca i8, align 1
  %2 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([3 x i8], ptr @.str.2, i64 0, i64 0), ptr noundef %1)
  %3 = load i8, ptr %1, align 1
  %4 = sext i8 %3 to i64
  ret i64 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @getarray(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store ptr %0, ptr %2, align 8
  %5 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([5 x i8], ptr @.str, i64 0, i64 0), ptr noundef %3)
  store i64 0, ptr %4, align 8
  br label %6

6:                                                ; preds = %15, %1
  %7 = load i64, ptr %4, align 8
  %8 = load i64, ptr %3, align 8
  %9 = icmp slt i64 %7, %8
  br i1 %9, label %10, label %18

10:                                               ; preds = %6
  %11 = load ptr, ptr %2, align 8
  %12 = load i64, ptr %4, align 8
  %13 = getelementptr inbounds i64, ptr %11, i64 %12
  %14 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([5 x i8], ptr @.str, i64 0, i64 0), ptr noundef %13)
  br label %15

15:                                               ; preds = %10
  %16 = load i64, ptr %4, align 8
  %17 = add nsw i64 %16, 1
  store i64 %17, ptr %4, align 8
  br label %6, !llvm.loop !9

18:                                               ; preds = %6
  %19 = load i64, ptr %3, align 8
  ret i64 %19
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @getfarray(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store ptr %0, ptr %2, align 8
  %5 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([5 x i8], ptr @.str, i64 0, i64 0), ptr noundef %3)
  store i64 0, ptr %4, align 8
  br label %6

6:                                                ; preds = %15, %1
  %7 = load i64, ptr %4, align 8
  %8 = load i64, ptr %3, align 8
  %9 = icmp slt i64 %7, %8
  br i1 %9, label %10, label %18

10:                                               ; preds = %6
  %11 = load ptr, ptr %2, align 8
  %12 = load i64, ptr %4, align 8
  %13 = getelementptr inbounds double, ptr %11, i64 %12
  %14 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef getelementptr inbounds ([4 x i8], ptr @.str.1, i64 0, i64 0), ptr noundef %13)
  br label %15

15:                                               ; preds = %10
  %16 = load i64, ptr %4, align 8
  %17 = add nsw i64 %16, 1
  store i64 %17, ptr %4, align 8
  br label %6, !llvm.loop !10

18:                                               ; preds = %6
  %19 = load i64, ptr %3, align 8
  ret i64 %19
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putint(i64 noundef %0) #0 {
  %2 = alloca i64, align 8
  store i64 %0, ptr %2, align 8
  %3 = load i64, ptr %2, align 8
  %4 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([5 x i8], ptr @.str, i64 0, i64 0), i64 noundef %3)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putfloat(double noundef %0) #0 {
  %2 = alloca double, align 8
  store double %0, ptr %2, align 8
  %3 = load double, ptr %2, align 8
  %4 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([4 x i8], ptr @.str.1, i64 0, i64 0), double noundef %3)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putch(i64 noundef %0) #0 {
  %2 = alloca i64, align 8
  store i64 %0, ptr %2, align 8
  %3 = load i64, ptr %2, align 8
  %4 = trunc i64 %3 to i32
  %5 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([3 x i8], ptr @.str.2, i64 0, i64 0), i32 noundef %4)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putarray(i64 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i64, align 8
  store i64 %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %6 = load i64, ptr %3, align 8
  %7 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([6 x i8], ptr @.str.3, i64 0, i64 0), i64 noundef %6)
  store i64 0, ptr %5, align 8
  br label %8

8:                                                ; preds = %18, %2
  %9 = load i64, ptr %5, align 8
  %10 = load i64, ptr %3, align 8
  %11 = icmp slt i64 %9, %10
  br i1 %11, label %12, label %21

12:                                               ; preds = %8
  %13 = load ptr, ptr %4, align 8
  %14 = load i64, ptr %5, align 8
  %15 = getelementptr inbounds i64, ptr %13, i64 %14
  %16 = load i64, ptr %15, align 8
  %17 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([6 x i8], ptr @.str.4, i64 0, i64 0), i64 noundef %16)
  br label %18

18:                                               ; preds = %12
  %19 = load i64, ptr %5, align 8
  %20 = add nsw i64 %19, 1
  store i64 %20, ptr %5, align 8
  br label %8, !llvm.loop !11

21:                                               ; preds = %8
  %22 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([2 x i8], ptr @.str.5, i64 0, i64 0))
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putfarray(i64 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i64, align 8
  store i64 %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %6 = load i64, ptr %3, align 8
  %7 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([6 x i8], ptr @.str.3, i64 0, i64 0), i64 noundef %6)
  store i64 0, ptr %5, align 8
  br label %8

8:                                                ; preds = %18, %2
  %9 = load i64, ptr %5, align 8
  %10 = load i64, ptr %3, align 8
  %11 = icmp slt i64 %9, %10
  br i1 %11, label %12, label %21

12:                                               ; preds = %8
  %13 = load ptr, ptr %4, align 8
  %14 = load i64, ptr %5, align 8
  %15 = getelementptr inbounds double, ptr %13, i64 %14
  %16 = load double, ptr %15, align 8
  %17 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([5 x i8], ptr @.str.6, i64 0, i64 0), double noundef %16)
  br label %18

18:                                               ; preds = %12
  %19 = load i64, ptr %5, align 8
  %20 = add nsw i64 %19, 1
  store i64 %20, ptr %5, align 8
  br label %8, !llvm.loop !12

21:                                               ; preds = %8
  %22 = call i32 (ptr, ...) @printf(ptr noundef getelementptr inbounds ([2 x i8], ptr @.str.5, i64 0, i64 0))
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_sysy_starttime(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = load i32, ptr @_sysy_idx, align 4
  %5 = sext i32 %4 to i64
  %6 = getelementptr inbounds [1024 x i32], ptr @_sysy_l1, i64 0, i64 %5
  store i32 %3, ptr %6, align 4
  %7 = call i32 @gettimeofday(ptr noundef @_sysy_start, ptr noundef null) #3
  ret void
}

; Function Attrs: nounwind
declare i32 @gettimeofday(ptr noundef, ptr noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_sysy_stoptime(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = call i32 @gettimeofday(ptr noundef @_sysy_end, ptr noundef null) #3
  %4 = load i32, ptr %2, align 4
  %5 = load i32, ptr @_sysy_idx, align 4
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [1024 x i32], ptr @_sysy_l2, i64 0, i64 %6
  store i32 %4, ptr %7, align 4
  %8 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_end, i32 0, i32 0), align 8
  %9 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_start, i32 0, i32 0), align 8
  %10 = sub nsw i64 %8, %9
  %11 = mul nsw i64 1000000, %10
  %12 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_end, i32 0, i32 1), align 8
  %13 = add nsw i64 %11, %12
  %14 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_start, i32 0, i32 1), align 8
  %15 = sub nsw i64 %13, %14
  %16 = load i32, ptr @_sysy_idx, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %17
  %19 = load i32, ptr %18, align 4
  %20 = sext i32 %19 to i64
  %21 = add nsw i64 %20, %15
  %22 = trunc i64 %21 to i32
  store i32 %22, ptr %18, align 4
  %23 = load i32, ptr @_sysy_idx, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %24
  %26 = load i32, ptr %25, align 4
  %27 = sdiv i32 %26, 1000000
  %28 = load i32, ptr @_sysy_idx, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %29
  %31 = load i32, ptr %30, align 4
  %32 = add nsw i32 %31, %27
  store i32 %32, ptr %30, align 4
  %33 = load i32, ptr @_sysy_idx, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %34
  %36 = load i32, ptr %35, align 4
  %37 = srem i32 %36, 1000000
  store i32 %37, ptr %35, align 4
  %38 = load i32, ptr @_sysy_idx, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %39
  %41 = load i32, ptr %40, align 4
  %42 = sdiv i32 %41, 60
  %43 = load i32, ptr @_sysy_idx, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %44
  %46 = load i32, ptr %45, align 4
  %47 = add nsw i32 %46, %42
  store i32 %47, ptr %45, align 4
  %48 = load i32, ptr @_sysy_idx, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %49
  %51 = load i32, ptr %50, align 4
  %52 = srem i32 %51, 60
  store i32 %52, ptr %50, align 4
  %53 = load i32, ptr @_sysy_idx, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %54
  %56 = load i32, ptr %55, align 4
  %57 = sdiv i32 %56, 60
  %58 = load i32, ptr @_sysy_idx, align 4
  %59 = sext i32 %58 to i64
  %60 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %59
  %61 = load i32, ptr %60, align 4
  %62 = add nsw i32 %61, %57
  store i32 %62, ptr %60, align 4
  %63 = load i32, ptr @_sysy_idx, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %64
  %66 = load i32, ptr %65, align 4
  %67 = srem i32 %66, 60
  store i32 %67, ptr %65, align 4
  %68 = load i32, ptr @_sysy_idx, align 4
  %69 = add nsw i32 %68, 1
  store i32 %69, ptr @_sysy_idx, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @starttime() #0 {
  call void @_sysy_starttime(i32 noundef 95)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @stoptime() #0 {
  call void @_sysy_stoptime(i32 noundef 96)
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4, !5}

!0 = !{!"Ubuntu clang version 14.0.6"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 1}
!5 = !{i32 7, !"frame-pointer", i32 2}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
