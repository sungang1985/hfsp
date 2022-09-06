<template>
    <el-menu class="el-menu-demo" mode="horizontal" :ellipsis="false">
        <el-menu-item index="0">HFSP</el-menu-item>
        <el-sub-menu index="2">
            <template #title>文件</template>
            <el-menu-item index="2-1">打开文件</el-menu-item>
            <el-menu-item index="2-2">保存文件</el-menu-item>
        </el-sub-menu>
    </el-menu>
</template>

<script>
export default {
    mounted() {
        console.log(`the BaseHeader component is now mounted.`);
    }
};
</script>
<style>
</style>