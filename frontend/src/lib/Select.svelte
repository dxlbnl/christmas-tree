<script lang='ts'>
  export let options: string[] = [];
  export let value: string;
</script>

<select
  bind:value
  on:change
>
  {#each options as option (option)}
    <option value={option}>{option}</option>
  {/each}
</select>