import type { PageLoad } from './$types';
 
export const load = (async ({ fetch }) => {
  const request = await fetch('http://kerstboom.local/program')
  const programs = await request.json()
  return {
    programs
  };
}) satisfies PageLoad;