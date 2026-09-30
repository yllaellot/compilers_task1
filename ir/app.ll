; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noreturn nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [32768 x i32], align 16
  %2 = alloca [32768 x i32], align 16
  %3 = bitcast [32768 x i32]* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 131072, i8* nonnull %3) #3
  %4 = bitcast [32768 x i32]* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 131072, i8* nonnull %4) #3
  %5 = getelementptr inbounds [32768 x i32], [32768 x i32]* %1, i64 0, i64 0
  br label %6

6:                                                ; preds = %6, %0
  %7 = phi i64 [ 0, %0 ], [ %13, %6 ]
  %8 = tail call i32 (...) @simRand() #3
  %9 = and i32 %8, 3
  %10 = icmp eq i32 %9, 0
  %11 = zext i1 %10 to i32
  %12 = getelementptr inbounds [32768 x i32], [32768 x i32]* %1, i64 0, i64 %7
  store i32 %11, i32* %12, align 4, !tbaa !5
  %13 = add nuw nsw i64 %7, 1
  %14 = icmp eq i64 %13, 32768
  br i1 %14, label %15, label %6, !llvm.loop !9

15:                                               ; preds = %6
  %16 = getelementptr inbounds [32768 x i32], [32768 x i32]* %2, i64 0, i64 0
  br label %17

17:                                               ; preds = %69, %15
  %18 = phi i32* [ %16, %15 ], [ %19, %69 ]
  %19 = phi i32* [ %5, %15 ], [ %18, %69 ]
  br label %20

20:                                               ; preds = %25, %17
  %21 = phi i64 [ 0, %17 ], [ %26, %25 ]
  %22 = shl nsw i64 %21, 8
  %23 = trunc i64 %21 to i32
  %24 = mul i32 %23, 6
  br label %28

25:                                               ; preds = %47
  %26 = add nuw nsw i64 %21, 1
  %27 = icmp eq i64 %26, 128
  br i1 %27, label %50, label %20, !llvm.loop !11

28:                                               ; preds = %47, %20
  %29 = phi i64 [ 0, %20 ], [ %48, %47 ]
  %30 = add nuw nsw i64 %29, %22
  %31 = getelementptr inbounds i32, i32* %19, i64 %30
  %32 = load i32, i32* %31, align 4, !tbaa !5
  %33 = icmp eq i32 %32, 0
  %34 = select i1 %33, i32 -16777216, i32 -16711936
  %35 = trunc i64 %29 to i32
  %36 = mul i32 %35, 6
  %37 = or i32 %36, 1
  %38 = add i32 %36, 2
  %39 = add i32 %36, 3
  %40 = add i32 %36, 4
  %41 = add i32 %36, 5
  br label %42

42:                                               ; preds = %42, %28
  %43 = phi i32 [ 0, %28 ], [ %45, %42 ]
  %44 = add nuw nsw i32 %43, %24
  tail call void @simPutPixel(i32 noundef %36, i32 noundef %44, i32 noundef %34) #3
  tail call void @simPutPixel(i32 noundef %37, i32 noundef %44, i32 noundef %34) #3
  tail call void @simPutPixel(i32 noundef %38, i32 noundef %44, i32 noundef %34) #3
  tail call void @simPutPixel(i32 noundef %39, i32 noundef %44, i32 noundef %34) #3
  tail call void @simPutPixel(i32 noundef %40, i32 noundef %44, i32 noundef %34) #3
  tail call void @simPutPixel(i32 noundef %41, i32 noundef %44, i32 noundef %34) #3
  %45 = add nuw nsw i32 %43, 1
  %46 = icmp eq i32 %45, 6
  br i1 %46, label %47, label %42, !llvm.loop !12

47:                                               ; preds = %42
  %48 = add nuw nsw i64 %29, 1
  %49 = icmp eq i64 %48, 256
  br i1 %49, label %25, label %28, !llvm.loop !13

50:                                               ; preds = %25
  tail call void (...) @simFlush() #3
  br label %51

51:                                               ; preds = %63, %50
  %52 = phi i64 [ 0, %50 ], [ %64, %63 ]
  %53 = icmp eq i64 %52, 0
  %54 = icmp eq i64 %52, 127
  %55 = shl i64 %52, 8
  %56 = trunc i64 %55 to i32
  %57 = add i32 %56, -256
  %58 = select i1 %53, i32 32512, i32 %57
  %59 = add i32 %56, 256
  %60 = select i1 %54, i32 0, i32 %59
  %61 = sext i32 %60 to i64
  %62 = sext i32 %58 to i64
  br label %70

63:                                               ; preds = %125
  %64 = add nuw nsw i64 %52, 1
  %65 = icmp eq i64 %64, 128
  br i1 %65, label %66, label %51, !llvm.loop !14

66:                                               ; preds = %63
  %67 = tail call i32 (...) @simHasClick() #3
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %69, label %130

69:                                               ; preds = %130, %66
  br label %17

70:                                               ; preds = %125, %51
  %71 = phi i64 [ 0, %51 ], [ %77, %125 ]
  %72 = icmp eq i64 %71, 0
  %73 = trunc i64 %71 to i32
  %74 = add i32 %73, -1
  %75 = select i1 %72, i32 255, i32 %74
  %76 = icmp eq i64 %71, 255
  %77 = add nuw nsw i64 %71, 1
  %78 = trunc i64 %77 to i32
  %79 = select i1 %76, i32 0, i32 %78
  %80 = add nsw i32 %75, %58
  %81 = sext i32 %80 to i64
  %82 = getelementptr inbounds i32, i32* %19, i64 %81
  %83 = load i32, i32* %82, align 4, !tbaa !5
  %84 = add nuw nsw i64 %71, %62
  %85 = getelementptr inbounds i32, i32* %19, i64 %84
  %86 = load i32, i32* %85, align 4, !tbaa !5
  %87 = add nsw i32 %86, %83
  %88 = add nsw i32 %79, %58
  %89 = sext i32 %88 to i64
  %90 = getelementptr inbounds i32, i32* %19, i64 %89
  %91 = load i32, i32* %90, align 4, !tbaa !5
  %92 = add nsw i32 %87, %91
  %93 = sext i32 %75 to i64
  %94 = add nuw nsw i64 %55, %93
  %95 = getelementptr inbounds i32, i32* %19, i64 %94
  %96 = load i32, i32* %95, align 4, !tbaa !5
  %97 = add nsw i32 %92, %96
  %98 = sext i32 %79 to i64
  %99 = add nuw nsw i64 %55, %98
  %100 = getelementptr inbounds i32, i32* %19, i64 %99
  %101 = load i32, i32* %100, align 4, !tbaa !5
  %102 = add nsw i32 %97, %101
  %103 = add nsw i32 %75, %60
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds i32, i32* %19, i64 %104
  %106 = load i32, i32* %105, align 4, !tbaa !5
  %107 = add nsw i32 %102, %106
  %108 = add nuw nsw i64 %71, %61
  %109 = getelementptr inbounds i32, i32* %19, i64 %108
  %110 = load i32, i32* %109, align 4, !tbaa !5
  %111 = add nsw i32 %107, %110
  %112 = add nsw i32 %79, %60
  %113 = sext i32 %112 to i64
  %114 = getelementptr inbounds i32, i32* %19, i64 %113
  %115 = load i32, i32* %114, align 4, !tbaa !5
  %116 = add nsw i32 %111, %115
  %117 = add nuw nsw i64 %71, %55
  %118 = icmp eq i32 %116, 3
  br i1 %118, label %125, label %119

119:                                              ; preds = %70
  %120 = getelementptr inbounds i32, i32* %19, i64 %117
  %121 = load i32, i32* %120, align 4, !tbaa !5
  %122 = icmp ne i32 %121, 0
  %123 = icmp eq i32 %116, 2
  %124 = select i1 %122, i1 %123, i1 false
  br label %125

125:                                              ; preds = %119, %70
  %126 = phi i1 [ true, %70 ], [ %124, %119 ]
  %127 = zext i1 %126 to i32
  %128 = getelementptr inbounds i32, i32* %18, i64 %117
  store i32 %127, i32* %128, align 4, !tbaa !5
  %129 = icmp eq i64 %77, 256
  br i1 %129, label %63, label %70, !llvm.loop !15

130:                                              ; preds = %66, %130
  %131 = tail call i32 (...) @simGetClick() #3
  %132 = lshr i32 %131, 16
  %133 = trunc i32 %132 to i16
  %134 = sdiv i16 %133, 6
  %135 = trunc i32 %131 to i16
  %136 = udiv i16 %135, 6
  %137 = shl i16 %136, 8
  %138 = add i16 %137, 32512
  %139 = and i16 %138, 32512
  %140 = zext i16 %139 to i32
  %141 = insertelement <2 x i16> poison, i16 %134, i64 0
  %142 = shufflevector <2 x i16> %141, <2 x i16> poison, <2 x i32> zeroinitializer
  %143 = add nsw <2 x i16> %142, <i16 256, i16 257>
  %144 = srem <2 x i16> %143, <i16 256, i16 256>
  %145 = sext <2 x i16> %144 to <2 x i32>
  %146 = insertelement <2 x i32> poison, i32 %140, i64 0
  %147 = shufflevector <2 x i32> %146, <2 x i32> poison, <2 x i32> zeroinitializer
  %148 = add nsw <2 x i32> %147, %145
  %149 = sext <2 x i32> %148 to <2 x i64>
  %150 = extractelement <2 x i64> %149, i64 0
  %151 = getelementptr inbounds i32, i32* %18, i64 %150
  store i32 1, i32* %151, align 4, !tbaa !5
  %152 = extractelement <2 x i64> %149, i64 1
  %153 = getelementptr inbounds i32, i32* %18, i64 %152
  store i32 1, i32* %153, align 4, !tbaa !5
  %154 = add nsw i16 %134, 255
  %155 = srem i16 %154, 256
  %156 = sext i16 %155 to i32
  %157 = and i16 %137, 32512
  %158 = zext i16 %157 to i32
  %159 = add nsw i32 %156, %158
  %160 = sext i32 %159 to i64
  %161 = getelementptr inbounds i32, i32* %18, i64 %160
  store i32 1, i32* %161, align 4, !tbaa !5
  %162 = extractelement <2 x i32> %145, i64 0
  %163 = add nsw i32 %162, %158
  %164 = sext i32 %163 to i64
  %165 = getelementptr inbounds i32, i32* %18, i64 %164
  store i32 1, i32* %165, align 4, !tbaa !5
  %166 = add i16 %137, 256
  %167 = and i16 %166, 32512
  %168 = zext i16 %167 to i32
  %169 = add nsw i32 %162, %168
  %170 = sext i32 %169 to i64
  %171 = getelementptr inbounds i32, i32* %18, i64 %170
  store i32 1, i32* %171, align 4, !tbaa !5
  %172 = tail call i32 (...) @simHasClick() #3
  %173 = icmp eq i32 %172, 0
  br i1 %173, label %69, label %130, !llvm.loop !16
}

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

declare void @simFlush(...) local_unnamed_addr #2

declare i32 @simHasClick(...) local_unnamed_addr #2

declare i32 @simGetClick(...) local_unnamed_addr #2

declare i32 @simRand(...) local_unnamed_addr #2

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

attributes #0 = { noreturn nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly mustprogress nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
!15 = distinct !{!15, !10}
!16 = distinct !{!16, !10}
